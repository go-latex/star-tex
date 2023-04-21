// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package main

import (
	"fmt"
	"io/fs"
	"os"
	"path"
	"path/filepath"
	"reflect"
	"testing"

	"star-tex.org/x/tex/internal/tds"
)

func TestProcess(t *testing.T) {
	dir, err := os.MkdirTemp("", "kpath-find-")
	if err != nil {
		t.Fatalf("could not create tmp dir: %+v", err)
	}
	defer os.RemoveAll(dir)

	dbname := path.Join(dir, "ls-R")
	err = os.WriteFile(dbname, []byte(`%%
./:
./dir1:
file1.tex

./dir2:
file2.tex

./dir3:
file2.tex
`), 0644)
	if err != nil {
		t.Fatalf("could not create texmf db: %+v", err)
	}
	db := os.DirFS(dir)

	for _, tc := range []struct {
		name string
		db   fs.FS
		all  bool
		want []string
		err  error
	}{
		{
			name: "file1.tex",
			db:   db,
			want: []string{path.Join("dir1", "file1.tex")},
		},
		{
			name: "file2.tex",
			db:   db,
			all:  true,
			want: []string{
				path.Join("dir2", "file2.tex"),
				path.Join("dir3", "file2.tex"),
			},
		},
		{
			name: "file2.tex",
			db:   db,
			err:  fmt.Errorf(`kpath: too many hits for file "file2.tex" (n=2)`),
		},
		{
			name: "err-walk-filesystem",
			db:   fsErrorTree{},
			err: fmt.Errorf(
				`could not create kpath context: kpath: could not walk fs: no stat`,
			),
		},
		{
			name: "plain.tex",
			db:   tds.FS,
			want: []string{
				path.Join("tex", "plain", "base", "plain.tex"),
			},
		},
	} {
		t.Run(tc.name, func(t *testing.T) {
			got, err := process(tc.name, tc.db, tc.all)
			switch {
			case err == nil && tc.err == nil:
				// ok.
			case err != nil && tc.err != nil:
				if got, want := err.Error(), tc.err.Error(); got != want {
					t.Fatalf("invalid error:\ngot= %s\nwant=%s\n", got, want)
				}
				return
			case err != nil && tc.err == nil:
				t.Fatalf("could not run kpath-find: %+v", err)
			case err == nil && tc.err != nil:
				t.Fatalf("missing error. expected: %+v", tc.err)
			}
			got = cleanup(dir, got)
			if !reflect.DeepEqual(got, tc.want) {
				t.Fatalf("invalid file named:\ngot= %q\nwant=%q", got, tc.want)
			}
		})
	}
}

func cleanup(dir string, vs []string) []string {
	for i, v := range vs {
		vs[i] = filepath.ToSlash(relto(dir, v))
	}
	return vs
}

func relto(base string, p string) string {
	v, err := filepath.Rel(base, p)
	if err != nil {
		return p
	}
	return v
}

type fsErrorTree struct{}

var (
	_ fs.FS     = (*fsErrorTree)(nil)
	_ fs.StatFS = (*fsErrorTree)(nil)
)

func (fsErrorTree) Open(name string) (fs.File, error) {
	return nil, fmt.Errorf("no such file %q", name)
}

func (fsErrorTree) Stat(name string) (fs.FileInfo, error) {
	return nil, fmt.Errorf("no stat")
}
