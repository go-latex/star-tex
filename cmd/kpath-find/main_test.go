// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package main

import (
	"fmt"
	"os"
	"path/filepath"
	"reflect"
	"testing"
)

func TestProcess(t *testing.T) {
	dir, err := os.MkdirTemp("", "kpath-find-")
	if err != nil {
		t.Fatalf("could not create tmp dir: %+v", err)
	}
	defer os.RemoveAll(dir)

	dbname := filepath.Join(dir, "ls-R")
	err = os.WriteFile(dbname, []byte(`%%
./:
./dir1:
file1.tex

./dir2:
file2.tex

./dir3:
file2.tex
`), 0755)
	if err != nil {
		t.Fatalf("could not create texmf db: %+v", err)
	}

	for _, tc := range []struct {
		name   string
		dbname string
		all    bool
		want   []string
		err    error
	}{
		{
			name:   "file1.tex",
			dbname: dbname,
			want:   []string{filepath.Join(dir, "/dir1/file1.tex")},
		},
		{
			name:   "file2.tex",
			dbname: dbname,
			all:    true,
			want: []string{
				filepath.Join(dir, "/dir2/file2.tex"),
				filepath.Join(dir, "/dir3/file2.tex"),
			},
		},
		{
			name:   "file2.tex",
			dbname: dbname,
			err:    fmt.Errorf(`kpath: too many hits for file "file2.tex" (n=2)`),
		},
		{
			name:   "err-new-from-db",
			dbname: "/dev/full",
			err: fmt.Errorf(
				`could not create kpath context: ` +
					`kpath: could not parse db file: ` +
					`could not scan db file: bufio.Scanner: token too long`,
			),
		},
		{
			name:   "err-no-db-file",
			dbname: filepath.Join(dir, "not-there"),
			err: fmt.Errorf(
				`could not open texmf db %[1]q: `+
					`open %[1]s: no such file or directory`,
				filepath.Join(dir, "not-there"),
			),
		},
	} {
		t.Run(tc.name, func(t *testing.T) {
			got, err := process(tc.name, tc.dbname, tc.all)
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
