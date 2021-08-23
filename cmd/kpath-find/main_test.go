// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package main

import (
	"fmt"
	"io/fs"
	"os"
	stdpath "path"
	"reflect"
	"runtime"
	"testing"

	"star-tex.org/x/tex/internal/tds"
)

func TestProcess(t *testing.T) {
	dir, err := os.MkdirTemp("", "kpath-find-")
	if err != nil {
		t.Fatalf("could not create tmp dir: %+v", err)
	}
	defer os.RemoveAll(dir)

	dbname := stdpath.Join(dir, "ls-R")
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

	errNotThere := "no such file or directory"
	if runtime.GOOS == "windows" {
		errNotThere = "File not found."
	}

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
			want: []string{stdpath.Join(dir, "/dir1/file1.tex")},
		},
		{
			name: "file2.tex",
			db:   db,
			all:  true,
			want: []string{
				stdpath.Join(dir, "/dir2/file2.tex"),
				stdpath.Join(dir, "/dir3/file2.tex"),
			},
		},
		{
			name: "file2.tex",
			db:   db,
			err:  fmt.Errorf(`kpath: too many hits for file "file2.tex" (n=2)`),
		},
		{
			name: "err-no-db-file",
			db:   os.DirFS(stdpath.Join(dir, "not-there")),
			err: fmt.Errorf(
				`could not create kpath context: `+
					`kpath: could not walk fs: `+
					`%[1]s %[2]s/.: %[3]s`,
				openErr,
				stdpath.Join(dir, "not-there"),
				errNotThere,
			),
		},
		{
			name: "plain.tex",
			db:   tds.FS,
			want: []string{"tex/plain/base/plain.tex"},
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

			if !reflect.DeepEqual(got, tc.want) {
				t.Fatalf("invalid file named:\ngot= %q\nwant=%q", got, tc.want)
			}
		})
	}
}
