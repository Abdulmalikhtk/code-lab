# C++ Compilation

How a `.cpp` file becomes a running program, and what `g++` and `clang` actually
are on this Mac.

```
Machine     Apple Silicon (arm64), macOS Darwin 25.6
Compiler    Apple clang 21.0.0
Toolchain   /Library/Developer/CommandLineTools
Example     MALIKH_CODES/Linked_List/linked_list.cpp
```

---

## Contents

1. [The Four Stages](#1-the-four-stages)
2. [Stage 1 — Preprocessing](#2-stage-1--preprocessing)
3. [Stage 2 — Compilation](#3-stage-2--compilation)
4. [Stage 3 — Assembly](#4-stage-3--assembly)
5. [Stage 4 — Linking](#5-stage-4--linking)
6. [g++ vs clang on macOS](#6-g-vs-clang-on-macos)
7. [The C++17 Warning](#7-the-c17-warning)
8. [Compiler Flags](#8-compiler-flags)
9. [Compile Errors vs Link Errors](#9-compile-errors-vs-link-errors)
10. [Multi-File Compilation](#10-multi-file-compilation)
11. [Running the Program](#11-running-the-program)
12. [Common Mistakes](#12-common-mistakes)
13. [Quick Reference](#13-quick-reference)

---

## 1. The Four Stages

One command runs **four separate programs** in sequence:

```bash
g++ -std=c++17 linked_list.cpp -o linked_list
```

```
linked_list.cpp                     source code
      |
      v   1. PREPROCESSOR
linked_list.i                       expanded source
      |
      v   2. COMPILER
linked_list.s                       assembly
      |
      v   3. ASSEMBLER
linked_list.o                       machine code + symbol table
      |
      v   4. LINKER
linked_list                         executable
```

Measured on the real `linked_list.cpp` (a 5-line Hello World):

| Stage        | File   | Size          | Lines  |
| ------------ | ------ | ------------- | ------ |
| Source       | `.cpp` | 89 B          | 5      |
| Preprocessed | `.i`   | **3,012,368 B** | 64,191 |
| Assembly     | `.s`   | 53,110 B      | 1,398  |
| Object       | `.o`   | 10,384 B      | —      |
| Executable   | —      | 38,840 B      | —      |

89 bytes becomes 3 MB after preprocessing. That is `#include<iostream>` doing
its work.

Run each stage on its own:

```bash
g++ -std=c++17 -E linked_list.cpp -o linked_list.i   # stop after preprocessing
g++ -std=c++17 -S linked_list.i   -o linked_list.s   # stop after compiling
g++ -c            linked_list.s   -o linked_list.o   # stop after assembling
g++ -std=c++17    linked_list.o   -o linked_list     # link
```

---

## 2. Stage 1 — Preprocessing

```bash
g++ -std=c++17 -E linked_list.cpp -o linked_list.i
```

The preprocessor is a **text manipulator**. It does not understand C++ at all —
it just edits text. Three jobs:

1. **`#include`** — literally pastes the entire header file in place of the
   directive. `<iostream>` pulls in `<ostream>`, which pulls in `<ios>`,
   `<streambuf>`, `<locale>`, recursively. That is the 64,191 lines.
2. **Macros** — replaces every `#define` name with its value.
3. **Comments** — all `//` and `/* */` are deleted.

The tail of `linked_list.i`:

```cpp
extern __attribute__((__visibility__("default"))) wostream wcout;
...
} }
# 2 "linked_list.cpp" 2
using std::cout,std::endl;
int main(){
cout << "Hello World"<<endl;
}
```

The original five lines sit at the very **bottom**. Everything above is
`<iostream>`.

`# 2 "linked_list.cpp"` is a **line marker**. It tells the compiler "the next
line is line 2 of linked_list.cpp" — which is how error messages report real
line numbers instead of line 64,190.

> Header bloat is the main reason C++ builds are slow. Include only what is
> needed.

---

## 3. Stage 2 — Compilation

```bash
g++ -std=c++17 -S linked_list.i -o linked_list.s
```

The real compiler. **Every error worth caring about comes from here.**

| Phase             | Does                                                    |
| ----------------- | ------------------------------------------------------- |
| Lexical analysis  | Break text into tokens (`cout`, `<<`, `"Hello World"`)   |
| Syntax analysis   | Build a parse tree — catches missing `;`, bad braces     |
| Semantic analysis | Type checking, name lookup, overloads, template instantiation |
| Optimization      | Apply the `-O` level                                     |
| Code generation   | Emit assembly for the target CPU (here: **arm64**)       |

`main` compiled to ARM64:

```asm
_main:
	stp	x29, x30, [sp, #-16]!            ; save frame pointer + return address
	mov	x29, sp                          ; set up stack frame
	adrp	x0, __ZNSt3__14coutE@GOTPAGE     ; arg0 = address of std::cout
	ldr	x0, [x0, __ZNSt3__14coutE@GOTPAGEOFF]
	adrp	x1, l_.str@PAGE                  ; arg1 = "Hello World"
	add	x1, x1, l_.str@PAGEOFF
	bl	__ZNSt3__1lsB9nqe210106INS_...   ; call operator<<
	adrp	x1, ...endl...@PAGE              ; arg1 = std::endl
	bl	__ZNSt3__113basic_ostreamIcNS_...
	mov	w0, #0                           ; return 0
	ldp	x29, x30, [sp], #16              ; restore
	ret
```

Two things worth noticing:

**`cout << "Hello World" << endl;` becomes two function calls.** `<<` is an
operator overload — ordinary function calls underneath, chained left to right.

**`mov w0, #0`** — `main` returns 0 even though `return 0;` was never written.
C++ special-cases `main`: falling off the end implicitly returns 0. Any other
non-`void` function that does this is undefined behaviour.

### Name mangling

That symbol `__ZNSt3__1lsB9nqe210106INS_11char_traitsIcEEEER...` is really
`std::operator<<(std::ostream&, const char*)`.

C++ allows overloading, so many functions share the name `operator<<`. The
linker only sees flat symbol names and cannot handle duplicates. So the compiler
**mangles** each name, encoding namespace, template arguments and parameter
types into one unique string.

Decode them:

```bash
nm linked_list.o | c++filt
```

This is also why C++ cannot link against C without `extern "C"` — C does not
mangle.

---

## 4. Stage 3 — Assembly

```bash
g++ -c linked_list.s -o linked_list.o
```

A near-mechanical translation of assembly mnemonics into binary opcodes.
`mov w0, #0` becomes actual bytes.

```
linked_list.o: Mach-O 64-bit object arm64
```

The `.o` is **not runnable**. It holds machine code, a **symbol table**, and
holes. From `nm linked_list.o`:

```
0000000000000304 T __ZNKSt3__113basic_ostreamIcNS_11char_traitsIcEEE6sentry...
                 U __ZNKSt3__16locale9use_facetERNS0_2idE
                 U __ZNKSt3__18ios_base6getlocEv
                 U __Unwind_Resume
```

| Letter | Means                                                       |
| ------ | ----------------------------------------------------------- |
| `T`    | Defined **here**, in the text (code) section. Has an address |
| `U`    | **Undefined** — called here but not defined here. No address |

Those `U` entries are unresolved references: a promise that someone else must
provide them. Resolving them is the linker's entire job.

> Templates like `basic_ostream` appear as `T` even though nobody wrote them —
> they were instantiated from the header **into this object file**. That is why
> a 5-line program produces a 10 KB `.o`.

---

## 5. Stage 4 — Linking

```bash
g++ -std=c++17 linked_list.o -o linked_list
```

The linker:

1. **Combines** all `.o` files into one image
2. **Resolves symbols** — matches every `U` to a `T` somewhere
3. **Relocates** — assigns final addresses and patches every call site
4. **Adds the C++ runtime** — startup code that sets up the stack, initialises
   globals (including `std::cout` itself), calls `main`, then calls `exit()`
   with the return value

Result:

```
linked_list: Mach-O 64-bit executable arm64
```

### Static vs dynamic linking

```bash
$ otool -L linked_list
	/usr/lib/libc++.1.dylib          <- the C++ standard library
	/usr/lib/libSystem.B.dylib       <- libc / kernel interface
```

Those are **not** copied into the 38 KB executable. They are **dynamically
linked**, resolved at *load* time by the dynamic linker (`dyld` on macOS,
`ld.so` on Linux). Binaries stay small and the OS shares one copy of `libc++`
across every running program.

| Platform | Inspect shared libs |
| -------- | ------------------- |
| macOS    | `otool -L program`  |
| Linux    | `ldd program`       |

---

## 6. g++ vs clang on macOS

**On this Mac, `g++` is not GCC. It is Apple clang wearing a GCC name.**

Proof — all four commands are hardlinks to the identical binary (same inode):

```bash
$ ls -i /usr/bin/g++ /usr/bin/clang++ /usr/bin/gcc /usr/bin/clang
1152921500312571562 /usr/bin/clang
1152921500312571562 /usr/bin/clang++
1152921500312571562 /usr/bin/g++
1152921500312571562 /usr/bin/gcc
```

```bash
$ g++ --version
Apple clang version 21.0.0 (clang-2100.1.1.101)
Target: arm64-apple-darwin25.6.0
```

Typing `g++` runs clang. Apple keeps the name so that old Makefiles and
tutorials written for GCC keep working.

### The four names

| Command   | Driver for | Links libstdc++/libc++? |
| --------- | ---------- | ----------------------- |
| `gcc`     | C          | No                      |
| `g++`     | C++        | **Yes**                 |
| `clang`   | C          | No                      |
| `clang++` | C++        | **Yes**                 |

Same binary, but the **name it is invoked as** changes behaviour. Use `g++` or
`clang++` for C++ — the `++` variants automatically link the C++ standard
library. Compiling C++ with plain `gcc`/`clang` produces a wall of undefined
symbols at link time.

### GCC vs Clang, the real projects

| | **GCC** | **Clang / LLVM** |
| --- | --- | --- |
| Origin | GNU Project, 1987 | Apple + LLVM, 2007 |
| Default on | Linux | macOS, FreeBSD |
| Error messages | Terser | Clearer, with carets and fix-it hints |
| Compile speed | Slower | Faster |
| Std library | `libstdc++` | `libc++` |
| Sanitizers | Supported | Origin of ASan/UBSan/TSan |
| Licence | GPL | Apache 2.0 |

Both implement standard C++. For coursework and practice they are
interchangeable — code that compiles cleanly on one almost always compiles on
the other. Differences only surface with compiler-specific extensions, inline
assembly, or pragmas.

### Installing real GCC on macOS

Only needed for GCC-specific features. Homebrew will not overwrite `/usr/bin/g++`:

```bash
brew install gcc
g++-14 --version        # real GNU GCC, version-suffixed
```

`g++` stays clang; `g++-14` is the genuine article. Currently **not installed**
on this machine.

---

## 7. The C++17 Warning

Compiling without a `-std` flag:

```
$ g++ linked_list.cpp -o linked_list
linked_list.cpp:2:26: warning: use of multiple declarators in a single
      using declaration is a C++17 extension [-Wc++17-extensions]
    2 | using std::cout,std::endl;
      |                          ^
1 warning generated.
```

### Cause

Apple clang defaults to **C++14**, confirmed by the `__cplusplus` macro:

```bash
$ clang++ -dM -E -x c++ /dev/null | grep __cplusplus
#define __cplusplus 201402L          # 201402 = C++14

$ clang++ -std=c++17 -dM -E -x c++ /dev/null | grep __cplusplus
#define __cplusplus 201703L          # 201703 = C++17
```

The comma form of a using-declaration is a **C++17 feature**:

```cpp
using std::cout, std::endl;          // C++17
```

Clang accepts it anyway as a non-standard **extension** and warns. The build
succeeds and the program runs — but the code is not portable, and a stricter
compiler would reject it.

### Three ways to fix it

**1. Set the standard (best):**

```bash
g++ -std=c++17 linked_list.cpp -o linked_list
```

Compiles silently. Verified.

**2. Split the using-declarations** — works on any standard:

```cpp
using std::cout;
using std::endl;
```

**3. Qualify at the call site** — no `using` at all:

```cpp
std::cout << "Hello World" << std::endl;
```

### `__cplusplus` values

| Standard | Value      |
| -------- | ---------- |
| C++11    | `201103L`  |
| C++14    | `201402L`  |
| C++17    | `201703L`  |
| C++20    | `202002L`  |
| C++23    | `202302L`  |

> **Always pass `-std=`.** Relying on the compiler default means the same code
> behaves differently on a different machine.

---

## 8. Compiler Flags

```bash
g++ -std=c++17 -Wall -Wextra -g linked_list.cpp -o linked_list
```

| Flag | Does |
| ---- | ---- |
| `-std=c++17` | Language standard. Also `c++11`, `c++14`, `c++20`, `c++23` |
| `-o name` | Name the output file. Without it, output is `a.out` |
| `-Wall` | Enable common warnings. Turn on permanently |
| `-Wextra` | More warnings that `-Wall` misses |
| `-Werror` | Treat warnings as errors |
| `-g` | Include debug symbols, needed for `lldb`/`gdb` |
| `-O0` | No optimisation (default). Fastest builds, best debugging |
| `-O1` `-O2` `-O3` | Increasing optimisation. `-O2` is the usual release level |
| `-Os` | Optimise for size |
| `-E` | Stop after preprocessing |
| `-S` | Stop after compiling — emit assembly |
| `-c` | Stop after assembling — emit `.o` |
| `-I dir` | Add a header search directory |
| `-L dir` | Add a library search directory |
| `-l name` | Link library `libname` |
| `-fsanitize=address` | **ASan** — catch leaks, use-after-free, overflows at runtime |
| `-fsanitize=undefined` | **UBSan** — catch undefined behaviour |
| `-v` | Verbose: show every sub-command the driver runs |

### For linked list work

```bash
g++ -std=c++17 -Wall -Wextra -g -fsanitize=address linked_list.cpp -o linked_list
```

`-fsanitize=address` matters most here. Linked lists are all raw `new`/`delete`,
and ASan reports the exact line of a leaked node or a use-after-free — instead
of a silent wrong answer or a bare `Segmentation fault`.

---

## 9. Compile Errors vs Link Errors

The single most useful distinction when debugging a build.

| | **Compile error** | **Link error** |
| --- | --- | --- |
| Stage | 2 | 4 |
| Cause | Bad syntax or types | Symbol declared but never defined |
| Message | `error: expected ';'` | `Undefined symbols for architecture arm64` |
| Reports | File **and line number** | A mangled symbol name, **no line number** |

```cpp
void insertAtHead(Node*& head, int val);   // declared, never defined
insertAtHead(head, 5);                     // compiles fine, FAILS AT LINK
```

The compiler is satisfied — it saw a declaration. The linker looks for the body,
finds nothing, and errors.

**Undefined symbol** almost always means one of:

- The function was never written
- The name is misspelled, or the signature does not match the declaration
- A `.cpp` / `.o` file was left off the compile command
- A required library was not passed with `-l`
- A class member function was defined without the `ClassName::` prefix

---

## 10. Multi-File Compilation

Once the linked list outgrows one file:

```bash
g++ -std=c++17 -c node.cpp -o node.o        # compile separately
g++ -std=c++17 -c list.cpp -o list.o
g++ -std=c++17 -c main.cpp -o main.o
g++ node.o list.o main.o -o program         # link together
```

Each `.cpp` is a **translation unit**, compiled in complete isolation.
`list.cpp` has no idea `node.cpp` exists — they only meet at the linker.

That is the whole reason headers exist: to give each translation unit the
*declarations* it needs, while the *definitions* live in one `.cpp` and get
matched up at link time.

Change one file, recompile only that file, relink. Make and CMake automate this.

One-shot version (no intermediate `.o` files kept):

```bash
g++ -std=c++17 node.cpp list.cpp main.cpp -o program
```

### Header guards

Every header needs protection against being included twice in one translation
unit:

```cpp
#ifndef NODE_H
#define NODE_H

struct Node {
    int data;
    Node* next;
    Node(int val) { data = val; next = nullptr; }
};

#endif
```

Or the shorter non-standard-but-universal form:

```cpp
#pragma once
```

Without a guard, including the same header twice gives
`error: redefinition of 'Node'`.

---

## 11. Running the Program

```bash
./linked_list
```

The `./` is **mandatory**. `zsh` searches `PATH` for bare command names, and
`.` (the current directory) is not in `PATH` on macOS — a deliberate security
choice, so a stray file named `ls` in a downloaded folder cannot hijack the
shell.

Build and run in one line:

```bash
g++ -std=c++17 -Wall -Wextra linked_list.cpp -o linked_list && ./linked_list
```

`&&` means "run the second command only if the first succeeded". Without it, a
failed build silently runs the **previous** binary — and the edits appear to
have done nothing.

### A shell shortcut

In `~/.zshrc`:

```bash
cpprun() {
  g++ -std=c++17 -Wall -Wextra -g -fsanitize=address "$1" -o "${1%.cpp}" \
    && "./${1%.cpp}"
}
```

Then `source ~/.zshrc`, and from then on:

```bash
cpprun linked_list.cpp
```

`${1%.cpp}` strips the `.cpp` suffix to build the output name.

---

## 12. Common Mistakes

### Forgetting `.cpp`

```
$ g++ linked_list
ld: unsupported mach-o filetype (only MH_OBJECT and MH_DYLIB can be linked)
    in 'linked_list'
clang++: error: linker command failed with exit code 1
```

`g++` decides what to do with each argument by its **extension**:

| Extension | Treated as | Action |
| --------- | ---------- | ------ |
| `.cpp` `.cc` `.cxx` | C++ source | preprocess → compile → assemble → link |
| `.o` | Object file | link only |
| `.dylib` `.a` | Library | link only |
| **none** | Already compiled | **hand straight to the linker** |

`linked_list` has no extension, so g++ skipped the first three stages and gave
it to `ld`. But that file is a finished **executable** (`MH_EXECUTE`), and the
linker only accepts `MH_OBJECT` (`.o`) or `MH_DYLIB` (`.dylib`). An executable
is already linked — it cannot be linked again.

Fix: pass the source, or just run the binary.

```bash
g++ -std=c++17 linked_list.cpp -o linked_list    # compile (note .cpp)
./linked_list                                     # run (note ./)
```

### Naming the source and the binary

| Name              | What it is                |
| ----------------- | ------------------------- |
| `linked_list.cpp` | Source — what gets edited |
| `linked_list`     | Executable — what gets run |

`-o linked_list` is what names the output.

### Other frequent errors

| Symptom | Cause |
| ------- | ----- |
| `command not found: gtt` | Typo. The shell found no such program — nothing to do with C++ |
| `command not found: linked_list` | Missing `./` |
| `permission denied` | Not executable — `chmod +x linked_list` |
| `a.out` appears | `-o` was omitted |
| Edits have no effect | Ran the old binary; the build failed. Use `&&` |
| `Undefined symbols` | See [section 9](#9-compile-errors-vs-link-errors) |
| `redefinition of ...` | Missing header guard |

---

## 13. Quick Reference

```bash
# Everyday build and run
g++ -std=c++17 -Wall -Wextra -g file.cpp -o file && ./file

# With memory checking (use this for linked lists)
g++ -std=c++17 -Wall -Wextra -g -fsanitize=address file.cpp -o file && ./file

# Release build
g++ -std=c++17 -O2 file.cpp -o file

# Multiple files
g++ -std=c++17 a.cpp b.cpp main.cpp -o program

# Separate compile then link
g++ -std=c++17 -c a.cpp -o a.o
g++ a.o b.o -o program
```

### Inspecting each stage

```bash
g++ -std=c++17 -E file.cpp | tail -20      # source after preprocessing
g++ -std=c++17 -S file.cpp -o -            # assembly to stdout
g++ -std=c++17 -c file.cpp && nm file.o | c++filt   # demangled symbols
otool -L program                            # shared libraries (macOS)
file program                                # what kind of binary is it
g++ -v -std=c++17 file.cpp -o file          # every sub-command the driver runs
```

### Toolchain facts for this Mac

```
g++ == clang++ == gcc == clang    same binary, same inode
Apple clang 21.0.0                arm64-apple-darwin25.6.0
Default standard                  C++14  (__cplusplus == 201402L)
Standard library                  libc++ (/usr/lib/libc++.1.dylib)
Real GCC installed                No  (brew install gcc -> g++-14)
```
