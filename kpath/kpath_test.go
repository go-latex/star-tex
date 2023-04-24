// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package kpath

import (
	"fmt"
	"io"
	"os"
	stdpath "path"
	"path/filepath"
	"strings"
	"testing"
)

type namedFile struct {
	io.Reader
	name string
}

func (f namedFile) Name() string { return f.name }

func TestFindFromDB(t *testing.T) {
	const (
		dbname = "/usr/share/texmf-dist/ls-R"
		db     = `%% a fake ls-R db.
./:
.:
../texmf-dist:
hello.tex
world.tex
dup.tex

./dir1/dir11:
file-dir1.tex
dup.tex
base.tex

./dir2:
file-dir2.tex
file-dir2.tfm

./dir2/dir11:
base.tex

./dir3:
dup.tex

./dir4:
f1.bar
f1.bar.tex
f2.bar
f2.bar.sty
f3.bar
f3.bar.styx

./dir5:
some_file
some_file.txt
`
	)

	ctx, err := NewFromDB(namedFile{strings.NewReader(db), dbname})
	if err != nil {
		t.Fatal(err)
	}

	for _, tc := range []struct {
		name string
		want string
		err  error
	}{
		{
			name: "hello.tex",
			want: "/usr/share/texmf-dist/hello.tex",
		},
		{
			name: "hello",
			want: "/usr/share/texmf-dist/hello.tex",
		},
		{
			name: "world.tex",
			want: "/usr/share/texmf-dist/world.tex",
		},
		{
			name: "file-dir1.tex",
			want: "/usr/share/texmf-dist/dir1/dir11/file-dir1.tex",
		},
		{
			name: "dir11/file-dir1.tex",
			want: "/usr/share/texmf-dist/dir1/dir11/file-dir1.tex",
		},
		{
			name: "dir11/file-dir1",
			want: "/usr/share/texmf-dist/dir1/dir11/file-dir1.tex",
		},
		{
			name: "file-dir2.tfm",
			want: "/usr/share/texmf-dist/dir2/file-dir2.tfm",
		},
		{
			name: "file-dir2.tex",
			want: "/usr/share/texmf-dist/dir2/file-dir2.tex",
		},
		{
			name: "file-dir2",
			want: "/usr/share/texmf-dist/dir2/file-dir2.tex",
		},
		{
			name: "dup.tex",
			err:  fmt.Errorf(`kpath: too many hits for file "dup.tex" (n=3)`),
		},
		{
			name: "dir11/base",
			err:  fmt.Errorf(`kpath: too many hits for file "dir11/base" (n=2)`),
		},
		{
			name: "f1.bar.tex",
			want: "/usr/share/texmf-dist/dir4/f1.bar.tex",
		},
		{
			name: "f1.bar",
			want: "/usr/share/texmf-dist/dir4/f1.bar.tex",
		},
		{
			name: "f2.bar",
			want: "/usr/share/texmf-dist/dir4/f2.bar.sty",
		},
		{
			name: "f3.bar",
			want: "/usr/share/texmf-dist/dir4/f3.bar",
		},
		{
			name: "some_file",
			want: "/usr/share/texmf-dist/dir5/some_file",
		},
	} {
		t.Run(tc.name, func(t *testing.T) {
			got, err := ctx.Find(tc.name)
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

			if got != tc.want {
				t.Fatalf("invalid file named:\ngot= %s\nwant=%s", got, tc.want)
			}
		})
	}
}

func TestFindFromConfig(t *testing.T) {
	const cfg = `%% texmf.cnf configuration

TEXMFROOT = /usr/share
TEXMFDIST = $TEXMFROOT/texmf-dist
TEXMFMAIN = ${TEXMFDIST}

% Local additions to the distribution trees.
TEXMFLOCAL = /usr/local/share/texmf;/usr/share/texmf

% TEXMFSYSVAR, where *-sys store cached runtime data.
TEXMFSYSVAR = /var/lib/texmf

% TEXMFSYSCONFIG, where *-sys store configuration data.
TEXMFSYSCONFIG = /etc/texmf

% Per-user texmf tree(s) -- organized per the TDS, as usual.  To define
% more than one per-user tree, set this to a list of directories in
% braces, as described above.  (This used to be HOMETEXMF.)  ~ expands
% to %USERPROFILE% on Windows, $HOME otherwise.
TEXMFHOME = ~/texmf

% This is the value manipulated by tlmgr's auxtrees subcommand in the
% root texmf.cnf. Kpathsea warns about a literally empty string for a
% value, hence the empty braces.
TEXMFAUXTREES = {}

TEXMF = {$TEXMFCONFIG,$TEXMFVAR,$TEXMFHOME,!!$TEXMFSYSCONFIG,!!$TEXMFSYSVAR,!!$TEXMFLOCAL,!!$TEXMFDIST}

TEXMFDBS = {!!$TEXMFLOCAL,!!$TEXMFSYSCONFIG,!!$TEXMFSYSVAR,!!$TEXMFDIST}

SYSTEXMF = $TEXMFSYSVAR;$TEXMFLOCAL;$TEXMFDIST

TEXMFCACHE = $TEXMFSYSVAR;$TEXMFVAR

VARTEXFONTS = $TEXMFVAR/fonts

%%%%%%%%%%%%%%%%%%%%

TEXINPUTS.tex           = .;$TEXMF/tex/{plain,generic,}//
TEXINPUTS.fontinst      = .;$TEXMF/{tex,fonts/afm}//
TEXINPUTS.amstex        = .;$TEXMF/tex/{amstex,plain,generic,}//
TEXINPUTS.csplain       = .;$TEXMF/tex/{csplain,plain,generic,}//
TEXINPUTS.eplain        = .;$TEXMF/tex/{eplain,plain,generic,}//
TEXINPUTS.ftex          = .;$TEXMF/tex/{formate,plain,generic,}//
TEXINPUTS.mex           = .;$TEXMF/tex/{mex,plain,generic,}//
TEXINPUTS.texinfo       = .;$TEXMF/tex/{texinfo,plain,generic,}//

% support the original xdvi.  Must come before the generic settings.
PKFONTS.XDvi   = .;$TEXMF/%s;$VARTEXFONTS/pk/{%m,modeless}//
VFFONTS.XDvi   = .;$TEXMF/%s
PSHEADERS.XDvi = .;$TEXMF/%q{dvips,fonts/type1}//
TEXPICTS.XDvi  = .;$TEXMF/%q{dvips,tex}//

`

	defer func() {
		// FIXME(sbinet): implement config parser.
		err := recover()
		if err == nil {
			t.Fatalf("expected panic")
		}
	}()

	ctx, err := parseConfig(strings.NewReader(cfg))
	if err != nil {
		t.Fatal(err)
	}

	_ = ctx // FIXME(sbinet): test Find/FindAll
}

func TestFindFromFS(t *testing.T) {
	ctx := New()
	for _, tc := range []struct {
		name string
		want string
		err  error
	}{
		{
			name: "plain.tex",
			want: "tex/plain/base/plain.tex",
		},
		{
			name: "hyphen.tex",
			want: "tex/generic/hyphen/hyphen.tex",
		},
		{
			name: "cmr10.tfm",
			want: "fonts/tfm/public/cm/cmr10.tfm",
		},
		{
			name: "not-there.tex",
			err:  fmt.Errorf(`kpath: could not find file "not-there.tex"`),
		},
	} {
		t.Run(tc.name, func(t *testing.T) {
			got, err := ctx.Find(tc.name)
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

			if got != tc.want {
				t.Fatalf("invalid file named:\ngot= %s\nwant=%s", got, tc.want)
			}

			f, err := ctx.Open(got)
			if err != nil {
				t.Fatalf("could not open file %q: %+v", got, err)
			}
			defer f.Close()
		})
	}
}

func TestNewFromFS(t *testing.T) {

	dir, err := os.MkdirTemp("", "star-tex-kpath-")
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
`), 0644)
	if err != nil {
		t.Fatalf("could not create texmf db: %+v", err)
	}
	db := os.DirFS(dir)

	err = os.MkdirAll(filepath.Join(dir, "dir1"), 0755)
	if err != nil {
		t.Fatalf("could not create dir1: %+v", err)
	}

	err = os.WriteFile(filepath.Join(dir, "dir1", "file1.tex"), []byte(""), 0644)
	if err != nil {
		t.Fatalf("could not create dir1/file1.tex: %+v", err)
	}

	ctx, err := NewFromFS(db)
	if err != nil {
		t.Fatalf("could not create kpath context: %+v", err)
	}

	for _, tc := range []struct {
		name string
		want string
		err  error
		open error
	}{
		{
			name: "file1.tex",
			want: filepath.ToSlash(stdpath.Join(dir, "dir1", "file1.tex")),
		},
		{
			// test NewFromFS only considered ls-R informations.
			name: "file2.tex",
			want: filepath.ToSlash(stdpath.Join(dir, "dir2", "file2.tex")),
			open: openError(filepath.ToSlash(stdpath.Join(dir, "dir2", "file2.tex"))),
		},
	} {
		t.Run(tc.name, func(t *testing.T) {
			got, err := ctx.Find(tc.name)
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

			if got != tc.want {
				t.Fatalf("invalid file named:\ngot= %s\nwant=%s", got, tc.want)
			}

			f, err := ctx.Open(got)
			switch {
			case err == nil && tc.open == nil:
				// ok.
			case err != nil && tc.open != nil:
				if got, want := err.Error(), tc.open.Error(); got != want {
					t.Fatalf("invalid Open error:\ngot= %s\nwant=%s\n", got, want)
				}
				return
			case err != nil && tc.open == nil:
				t.Fatalf("could not run kpath-open: %+v", err)
			case err == nil && tc.open != nil:
				t.Fatalf("missing error. expected: %+v", tc.open)
			}
			defer f.Close()
		})
	}
}

func openError(name string) error {
	_, err := os.Open(name)
	if err == nil {
		panic(fmt.Errorf("opening %q should have failed", name))
	}
	return err
}
