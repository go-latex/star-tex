// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package xtex

import (
	"fmt"
	"io"
	"os"
	"strings"
	"unsafe"
)

type pasFile struct {
	*ioFile
}

func (f *pasFile) byte() byte { return f.component[0] }

func (f *pasFile) memoryWord() memoryWord {
	if g, e := uintptr(f.componentSize), unsafe.Sizeof(memoryWord{}); g != e { //TODO-
		panic(todo("invalid component: got %v, expected %v (%q)", g, e, f.name))
	}

	return *(*memoryWord)(unsafe.Pointer(&f.component))
}

func (f *pasFile) pMemoryWord() *memoryWord {
	if g, e := uintptr(f.componentSize), unsafe.Sizeof(memoryWord{}); g != e { //TODO-
		panic(todo("invalid component: got %v, expected %v (%q)", g, e, f.name))
	}

	return (*memoryWord)(unsafe.Pointer(&f.component))
}

func break1(f *pasFile)                                  { /* nop */ }
func breakIn(f *pasFile, b bool)                         { /* nop */ }
func close(f *pasFile)                                   { f.close() }
func eof(f *pasFile) bool                                { return f.ioFile.eof }
func eoln(f *pasFile) bool                               { return f.ioFile.eoln() }
func erstat(f *pasFile) int32                            { return f.erstat }
func get(f *pasFile)                                     { f.get() }
func put(f *pasFile)                                     { f.put() }
func reset1(t *Context, f *pasFile, name, mode string)   { reset(t, f, 1, name, mode) }
func reset4(t *Context, f *pasFile, name, mode string)   { reset(t, f, 4, name, mode) }
func rewrite1(t *Context, f *pasFile, name, mode string) { rewrite(t, f, 1, name, mode) }
func rewrite4(t *Context, f *pasFile, name, mode string) { rewrite(t, f, 4, name, mode) }

type readCloser struct {
	io.Reader
}

var (
	_ io.ReadCloser = readCloser{}
)

func (r readCloser) Close() error { return nil }

// [0] page 87
//
// Reset (F) initiates inspection (reading) of F by placing the file at its
// beginning. If F is not empty, the value of the first component of F is
// assigned to F and eof (F) becomes false.
func reset(ctx *Context, f *pasFile, componentSize int, name, mode string) {
	name = strings.TrimRight(name, " ")
	if !strings.Contains(mode, modeNoIOPanic) {
		panic(fmt.Errorf("unsupported file mode: %q (%q)", mode, name))
	}

	f.close()
	f.ioFile = nil
	if name == stdioDev {
		if isMain {
			f.ioFile = &ioFile{
				eof:           false,
				erstat:        0,
				componentSize: componentSize,
				name:          os.Stdin.Name(),
				in:            os.Stdin, //TODO bufio
			}
			return
		}

		fname := os.Stdin.Name()
		if f, ok := ctx.stdin.(interface{ Name() string }); ok {
			fname = f.Name()
		}

		f.ioFile = &ioFile{
			eof:           false,
			erstat:        0,
			componentSize: componentSize,
			name:          fname,
			in:            ctx.stdin,
		}
		return
	}

	g, err := os.Open(name)
ok:
	switch {
	case err != nil:
		switch {
		case name == texPool:
			f.ioFile = &ioFile{
				eof:           false,
				erstat:        0,
				componentSize: componentSize,
				name:          name,
				in:            readCloser{strings.NewReader(assets["/tex.pool"])},
			}
			break ok
		case strings.HasPrefix(name, texArea):
			if s, ok := assets["/texinputs/"+name[len(texArea):]]; ok {
				f.ioFile = &ioFile{
					eof:           false,
					erstat:        0,
					componentSize: componentSize,
					name:          name,
					in:            readCloser{strings.NewReader(s)},
				}
				break ok
			}
		case strings.HasPrefix(name, texFontArea):
			if s, ok := assets["/texfonts/"+name[len(texFontArea):]]; ok {
				f.ioFile = &ioFile{
					eof:           false,
					erstat:        0,
					componentSize: componentSize,
					name:          name,
					in:            readCloser{strings.NewReader(s)},
				}
				break ok
			}
		}

		f.ioFile = &ioFile{
			erstat:        1,
			componentSize: componentSize,
			name:          name,
		}
		return
	default:
		f.ioFile = &ioFile{
			eof:           false,
			erstat:        0,
			componentSize: componentSize,
			name:          name,
			in:            g, //TODO bufio
		}
	}

	if _, err := io.ReadFull(f.ioFile.in, f.ioFile.component[:f.ioFile.componentSize]); err != nil {
		f.ioFile.eof = true
		f.ioFile.erstat = 1
		f.ioFile.in.Close()
	}
}

// [0] page 88.
//
// Rewrite (F) initiates generation (writing) of the file F. The current value
// of F is replaced with the empty file. Eof(F) becomes true, and a new file
// may be written.
func rewrite(ctx *Context, f *pasFile, componentSize int, name, mode string) {
	name = strings.TrimRight(name, " ")
	if !strings.Contains(mode, modeNoIOPanic) {
		panic(fmt.Errorf("unsupported file mode: %q", mode))
	}

	f.close()
	f.ioFile = nil
	if name == stdioDev {
		if isMain {
			f.ioFile = &ioFile{
				eof:           true,
				erstat:        0,
				componentSize: componentSize,
				name:          os.Stdout.Name(),
				out:           os.Stdout, //TODO bufio
			}
			return
		}

		f.ioFile = &ioFile{
			eof:           true,
			erstat:        0,
			componentSize: componentSize,
			name:          os.Stdout.Name(),
			out:           ctx.stdout,
		}
		return
	}

	g, err := os.Create(name)
	if err != nil {
		f.ioFile = &ioFile{
			eof:           false,
			erstat:        1,
			componentSize: componentSize,
			name:          name,
		}
		return
	}

	f.ioFile = &ioFile{
		eof:           true,
		erstat:        0,
		componentSize: componentSize,
		name:          name,
		out:           g, //TODO bufio
	}
}

type ioFile struct {
	component     [unsafe.Sizeof(memoryWord{})]byte
	erstat        int32
	in            io.ReadCloser
	componentSize int
	name          string
	out           io.WriteCloser

	eof bool
	eol bool
}

func (f *ioFile) close() {
	if f == nil {
		return
	}

	if f.in != nil {
		if err := f.in.Close; err != nil {
			f.erstat = 1
		}
		f.eof = true
		f.in = nil
	}

	if f.out != nil {
		if err := f.out.Close; err != nil {
			f.erstat = 1
		}
		f.eof = false
		f.out = nil
	}
}

// [0] page 88
//
// Read (F, X) (for X, a variable) is equivalent to
//
// 	begin
// 		X := F^; Get(F)
// 	end
//
// Read (F, V1, ... , Vn) is equivalent to the statement
//
//	begin Read(F,V1); ... ;Read(F,Vn) end
func (f *ioFile) read(args []interface{}, nl bool) {
	f.eol = false
	for len(args) != 0 {
		arg := args[0]
		args = args[1:]
		if _, ok := getWidth(&args); ok {
			panic("internal error: read field width specifier not supported")
		}

		switch x := arg.(type) {
		case *byte:
			*x = f.component[0]
		default:
			panic(fmt.Errorf("unsupported read variable type: %T (%q)", x, f.name))
		}
		f.get()
	}
	if !nl {
		return
	}

	// [0] page 92
	//
	// ReadLn(F) skips to the beginning of the next line of the textfile F (F^
	// becomes the first character of the next line).
	for !f.eof && f.component[0] != '\n' {
		f.get()
	}
	if !f.eof {
		f.get()
	}
}

// [0] page 88
//
// Write(F, E) (for E, an expresion) is equivalent to
//
// 	begin
// 		F^ := E; Put(F)
// 	end
// Write (F, E1, ... , En) is equivalent to the statement
//
//	begin Write(F,E1); ... ; Write(F,En) end
func (f *ioFile) write(args []interface{}, nl bool) {
	for len(args) != 0 {
		arg := args[0]
		args = args[1:]
		w, ok := getWidth(&args)
		if _, ok2 := getWidth(&args); ok2 {
			panic("internal error: write fraction field width specifier not supported")
		}

		var err error
		switch x := arg.(type) {
		case string:
			_, err = f.out.Write([]byte(x))
		case byte:
			if ok {
				_, err = fmt.Fprintf(f.out, "%*d", w, x)
				break
			}

			f.component[0] = x
			f.put()
		case int32:
			if ok {
				_, err = fmt.Fprintf(f.out, "%*d", w, x)
				break
			}

			_, err = fmt.Fprint(f.out, x)
		case int:
			if ok {
				_, err = fmt.Fprintf(f.out, "%*d", w, x)
				break
			}

			_, err = fmt.Fprint(f.out, x)
		case uint16:
			if ok {
				_, err = fmt.Fprintf(f.out, "%*d", w, x)
				break
			}

			_, err = fmt.Fprint(f.out, x)
		default:
			panic(fmt.Errorf("unsupported write variable type: %T (%q)", x, f.name))
		}
		if err != nil {
			panic(fmt.Errorf("write I/O error: %v (%q)", err, f.name))
		}
	}
	// [0] page 92
	//
	// Writeln (F) terminates the current line of the textfile F.
	if nl {
		f.write([]interface{}{"\n"}, false)
	}
}

// [0] page 88
//
// Get(F) advances the file to the next component and assigns the value of this
// component to the buffer variable F^. If no next component exists, then
// eof(F) becomes true, and F^ becomes undefined. The effect of Get (F) is an
// error if eof(F) is true prior to its execution or if F is being generated.
func (f *ioFile) get() {
	if f.eof {
		panic(fmt.Errorf("get called at eof: %s", f.name))
	}

	f.eol = false
	if _, err := io.ReadFull(f.in, f.component[:f.componentSize]); err != nil {
		f.eof = true
		f.erstat = 1
		f.in.Close()
	}
}

// [0] page 88
//
// Put(F) appends the value of the buffer variable F^ to the file F. The effect
// is an error unless prior to execution the predicate eof(F) is true. eof(F)
// remains true, and F^ becomes undefined. Put(F) is an error if F is being
// inspected.
func (f *ioFile) put() {
	if !f.eof {
		panic(fmt.Errorf("put called not at eof: %s", f.name))
	}

	if _, err := f.out.Write(f.component[:f.componentSize]); err != nil {
		panic(fmt.Errorf("put I/O error: %v (%q)", err, f.name))
	}
}

// [0] page 92
//
// Eoln(F)
//
// a Boolean function indicating whether the end of the current line in the
// textfile F has been reached. (If true, F^ corresponds to the position of a
// line separator, but F^ is a blank.)
func (f *ioFile) eoln() bool {
	if f.eol || f.eof {
		return true
	}

	if f.component[0] != '\n' {
		return false
	}

	f.component[0] = ' '
	f.eol = true
	return true
}

type vaWidth int

func getWidth(args *[]interface{}) (int, bool) {
	s := *args
	if len(s) == 0 {
		return 0, false
	}

	x, ok := s[0].(vaWidth)
	if !ok {
		return 0, false
	}

	*args = s[1:]
	return int(x), true
}
