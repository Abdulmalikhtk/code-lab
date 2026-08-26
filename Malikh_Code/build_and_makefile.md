# Build Output and Makefiles

Keeping compiled binaries out of the repo, and automating the build so the flags
never have to be retyped.

```
Repo root   ~/Downloads/Practice1/code-lab
Compiler    g++  (Apple clang 21, arm64)
Standard    -std=c++17  (always pass it, the default here is C++14)
make        Already installed with the Command Line Tools
```

Why binaries are never committed is covered in [git_doc.md](git_doc.md).
What the compiler is doing is in [cpp_compilation.md](cpp_compilation.md).

---

## Contents

1. [The build/ Habit](#1-the-build-habit)
2. [Setting Up .gitignore](#2-setting-up-gitignore)
3. [Verifying It Worked](#3-verifying-it-worked)
4. [How make Works](#4-how-make-works)
5. [The Makefile](#5-the-makefile)
6. [Makefile Syntax Reference](#6-makefile-syntax-reference)
7. [make asan](#7-make-asan)
8. [Debugging a Makefile](#8-debugging-a-makefile)
9. [The Android Build System](#9-the-android-build-system)
10. [Common Errors](#10-common-errors)
11. [Quick Reference](#11-quick-reference)

---

## 1. The build/ Habit

One rule: **compiled output goes in `build/`, never next to the source.**

```
MALIKH_CODES/
├── Linked_List/
│   ├── Makefile           commit
│   ├── linked_list.cpp    commit
│   └── build/             ignored
│       └── linked_list
└── Stack/
    ├── Makefile
    ├── stack.cpp
    └── build/
```

By hand:

```bash
mkdir -p build && g++ -std=c++17 -Wall -Wextra -g linked_list.cpp -o build/linked_list && ./build/linked_list
```

`&&` matters. Without it, a failed build silently runs the **previous** binary
and the edits appear to have done nothing.

### Deleting a stray binary

If one is already sitting next to the source:

```bash
cd MALIKH_CODES/Linked_List
rm linked_list          # the binary, NOT linked_list.cpp
```

Safe as long as it was never committed. It rebuilds in one command.

---

## 2. Setting Up .gitignore

Create `.gitignore` at the **repo root** — `code-lab/.gitignore`, next to `.git`.

```gitignore
# Build output — one line, covers every build/ folder at any depth
build/

# Safety net: binaries that escape build/ by accident
*.o
*.out
*.exe
*.app
*.dSYM/
a.out

# Never ignore source or notes, no matter what matched above
!*.cpp
!*.h
!*.hpp
!*.md
!*.txt

# macOS clutter
.DS_Store
```

### Why one line is enough

`build/` has **no leading slash**, so it matches a directory named `build` at
*any* depth. It covers `MALIKH_CODES/Linked_List/build/`,
`AAFREN_CODES/anything/build/`, and every folder added in future.

Writing `/build/` with a leading slash would only match a `build` folder at the
repo root, which is useless for this layout.

The `*.o` / `*.out` block is a safety net for the day `-o build/...` gets
forgotten and a binary lands next to the source anyway.

### The trap: already-committed binaries

**`.gitignore` only affects untracked files.** Git keeps tracking anything it
already knows about, no matter what the ignore file says.

```bash
git rm --cached path/to/binary      # untrack it, keep the file on disk
git commit -m "Stop tracking binary"
```

`--cached` is critical. Without it, `git rm` deletes the file from disk too.

---

## 3. Verifying It Worked

```bash
cd ~/Downloads/Practice1/code-lab
git status
```

Expected: `.cpp`, `.md`, `Makefile` and `.gitignore` listed — and **no**
`build/`, no bare binary.

Git collapses new folders into a single entry. To see inside:

```bash
git status --untracked-files=all
```

Check one file and see which rule caught it:

```bash
git check-ignore -v MALIKH_CODES/Linked_List/build/linked_list
```

Expected:

```
.gitignore:2:build/	MALIKH_CODES/Linked_List/build/linked_list
```

Prints nothing if the file is **not** ignored — usually because `.gitignore` is
not at the repo root, or was saved as `gitignore` without the leading dot.

Then commit:

```bash
git add .
git status                                  # read this before committing
git commit -m "Add .gitignore, move binaries to build/"
git push
```

---

## 4. How make Works

`make` is not a script runner. It is a **dependency resolver**.

You do not tell it what steps to run. You tell it **what depends on what**, and
how to produce each thing. Make works out the order and skips anything already
up to date.

### Anatomy of a rule

```
target            prerequisites
   |                    |
   v                    v
build/linked_list: linked_list.cpp
        g++ -std=c++17 linked_list.cpp -o build/linked_list
^
TAB (mandatory)         ^-- recipe
```

| Part | Meaning |
| ---- | ------- |
| Target | The file this rule produces |
| Prerequisites | The files the target is built *from* |
| Recipe | Shell commands that do it. Each line starts with a **TAB** |

Read it as a sentence: *"`build/linked_list` is made from `linked_list.cpp`, by
running this command."*

### The algorithm

For each target, make asks two questions:

1. **Does the target file exist?** If no, run the recipe.
2. **Is any prerequisite newer than the target?** If yes, run the recipe.

Otherwise, do nothing.

That is the whole thing — a timestamp comparison.

```bash
$ make
g++ -std=c++17 -Wall -Wextra -g linked_list.cpp -o build/linked_list

$ make
make: Nothing to be done for 'all'.
```

The second run skipped because the source is older than the binary.
`Nothing to be done` is **not an error**.

> **The consequence.** Make trusts timestamps completely and never looks inside
> a file. This is why editing a header does not trigger a rebuild unless the
> header is listed as a prerequisite — you get a stale binary with no warning.

### The dependency graph

Rules chain. A target in one rule can be a prerequisite in another:

```
        program
         /    \
    main.o    list.o
      |         |
  main.cpp   list.cpp
```

Make walks this bottom-up. Edit only `list.cpp` and it recompiles `list.o`,
relinks `program`, and leaves `main.o` alone. Nobody wrote that logic — only
the edges were declared.

---

## 5. The Makefile

`make` ships with the Command Line Tools, so it is already installed.

A `Makefile` records the build recipe once, so `-std=c++17` can never be
forgotten and a collaborator can build without asking which flags to use.

The `Makefile` **is source code**. Commit it.

### The TAB rule

**Recipe lines must begin with a literal TAB character. Not spaces.**

Spaces produce an error that explains nothing:

```
Makefile:8: *** missing separator.  Stop.
```

VS Code **already handles this**. The bundled `make` extension ships this
default:

```json
"configurationDefaults": { "[makefile]": { "editor.insertSpaces": false } }
```

So pressing Tab in a Makefile inserts a real tab, with no configuration needed.
Two conditions:

- **The filename must be recognised.** The default applies to `Makefile`,
  `makefile`, `GNUmakefile`, `.mak`, `.mk`. Name it `Makefile.txt` and the
  editor treats it as plain text and uses spaces.
- **It only affects the Tab key, not pasted text.** Copying the file out of a
  rendered markdown preview or a browser can bring spaces with it.

### Verifying the tabs

```bash
awk '/^\t/{n++} END{print n+0}' Makefile
```

Must print **5** for the Makefile below — one per recipe line.

> Do **not** use `grep -P '^\t'`. `-P` is a GNU grep feature and macOS ships BSD
> grep, which rejects it with `grep: invalid option -- P`.

Or look at it directly — `cat -t` renders tabs as `^I`:

```bash
cat -t Makefile
```

```
$(BUILD)/%: %.cpp | $(BUILD)
^I$(CXX) $(CXXFLAGS) $< -o $@
```

If the recipe lines show spaces instead of `^I`, convert them:

```bash
sed -i '' 's/^    /\t/' Makefile
```

### The file

Save as `Makefile` — no extension, capital M. This version auto-detects every
`.cpp` in the folder, so adding `stack.cpp` later needs no edit.

```make
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -g
BUILD    := build

SRCS := $(wildcard *.cpp)
BINS := $(patsubst %.cpp,$(BUILD)/%,$(SRCS))

all: $(BINS)

$(BUILD)/%: %.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) $< -o $@

$(BUILD):
	mkdir -p $(BUILD)

run-%: $(BUILD)/%
	@./$(BUILD)/$*

list:
	@echo "Programs: $(notdir $(BINS))"

asan: CXXFLAGS += -fsanitize=address -fsanitize=undefined
asan: clean all

clean:
	rm -rf $(BUILD)

.PHONY: all list asan clean
```

The same file works unchanged in every project folder. Copy it as-is.

> **`run-%`, not `run F=<name>`.** An earlier version of this file used
> `run: $(BUILD)/$(F)`. That breaks badly when `F` is omitted: `$(F)` expands to
> nothing, the recipe becomes `./build/`, and the shell refuses to execute a
> directory —
>
> ```
> $ make run
> make: ./build/: Permission denied
> ```
>
> which says nothing about the real problem. The pattern-rule form needs no
> variable, supports tab completion, and fails clearly on a typo:
>
> ```
> $ make run-typo
> make: *** No rule to make target `run-typo'.  Stop.
> ```

### Line by line

| Line | Does |
| ---- | ---- |
| `CXX := g++` | Variable. Change the compiler in one place |
| `SRCS := $(wildcard *.cpp)` | Every `.cpp` in the folder → `linked_list.cpp` |
| `BINS := $(patsubst ...)` | Turns that into `build/linked_list` |
| `all: $(BINS)` | The **default goal** — the first target is what bare `make` builds. No recipe; it just depends on every binary |
| `$(BUILD)/%: %.cpp` | The engine. A **pattern rule** covering every program in the folder |
| `$(BUILD):` | A rule whose target is a **directory**. Runs once |
| `run-%: $(BUILD)/%` | Pattern rule. `make run-foo` builds `build/foo` first, then runs it. `$*` is the stem, `@` hides the echoed command |
| `list:` | Prints the available program names |
| `asan: CXXFLAGS += ...` | Appends flags **only** when the goal is `asan` |
| `asan: clean all` | Two rules, one target. Forces a clean rebuild |
| `clean:` | `rm -rf build` |
| `.PHONY:` | Marks command-targets so make does not treat them as filenames. `run-%` is a pattern rule and does **not** belong here |

### Usage

```bash
make                       # build every .cpp in the folder
make list                  # show the available program names
make run-linked_list       # build and run one program
make run-mylinkedlist      # a folder can hold many programs
make asan                  # rebuild with the sanitizers
make clean                 # delete build/
```

Force a full rebuild: `make clean && make`, or `make -B`.

A folder can hold as many programs as you like — `make` builds them all, and
each gets its own `run-` target automatically. Nothing in the Makefile needs
editing when a new `.cpp` is added.

---

## 6. Makefile Syntax Reference

### Variables

Use with `$(NAME)`. Parentheses are required for names longer than one
character.

| Form | Called | Behaviour |
| ---- | ------ | --------- |
| `:=` | Simple | Evaluated **once**, immediately. **Use this** |
| `=` | Recursive | Re-evaluated on every use. Can self-reference and hang |
| `?=` | Conditional | Assign only if not already set |
| `+=` | Append | Add to the existing value |

Command-line assignment beats what is in the file:

```bash
make CXXFLAGS="-std=c++20 -O2"
```

`CXX`, `CXXFLAGS`, `CC`, `CFLAGS`, `LDFLAGS` are conventional names that make's
built-in rules already use. Follow the convention.

### Automatic variables

Set by make per rule, so recipes never repeat filenames.

| Variable | Is |
| -------- | -- |
| `$@` | The **target** |
| `$<` | The **first** prerequisite |
| `$^` | **All** prerequisites, space-separated, deduplicated |
| `$*` | The **stem** — whatever `%` matched |

In the pattern rule, building `build/linked_list` from `linked_list.cpp`:

```make
$(CXX) $(CXXFLAGS) $< -o $@
#                  |     +-- build/linked_list
#                  +-------- linked_list.cpp
```

`$<` versus `$^` matters: compiling takes one source, linking takes all objects.

### Pattern rules

```make
$(BUILD)/%: %.cpp
```

`%` matches a **stem** and carries it across. `build/%` against
`build/linked_list` gives stem `linked_list`, so the prerequisite becomes
`linked_list.cpp`. One rule, unlimited files.

### `.PHONY`

Make assumes every target is a filename. `clean` is not — it is a command.

Without `.PHONY`, if a file named `clean` ever appeared in the folder, make
would see it, find it has no prerequisites, decide it is up to date, and print
`make: 'clean' is up to date.` — refusing to delete anything, for no visible
reason.

**Any target that is not a real file belongs in `.PHONY`.**

### Order-only prerequisites

```make
$(BUILD)/%: %.cpp | $(BUILD)
#                   ^ everything after | is order-only
```

Normal prerequisites trigger a rebuild when newer. Order-only ones only
guarantee ordering.

This is required for directories. A directory's timestamp updates every time a
file is written into it, so `build/` would always look newer than the binaries
inside it and make would rebuild everything on every run, forever. The `|` says
*"ensure this exists first, but ignore its timestamp."*

### Functions

| Function | Does |
| -------- | ---- |
| `$(wildcard pattern)` | Expand a glob against the filesystem |
| `$(patsubst from,to,text)` | Pattern substitution across a list |
| `$(shell cmd)` | Run a shell command, capture the output |
| `$(notdir path)` | Strip the directory part |
| `$(basename f)` | Strip the extension |

`wildcard` + `patsubst` is the standard idiom for "build everything here".

### Recipe gotchas

**Each recipe line runs in a separate shell.** State does not carry:

```make
bad:
	cd build          # this shell exits
	ls                # runs in the ORIGINAL directory
```

Chain with `&&` instead:

```make
good:
	cd build && ls
```

**`$` means make, not shell.** Double it to pass one through:

```make
	echo $$HOME       # shell variable
	echo $(HOME)      # make variable
```

**Line prefixes:**

| Prefix | Effect |
| ------ | ------ |
| `@` | Do not echo the command before running it |
| `-` | Ignore a non-zero exit code and keep going |

By default make stops immediately when a command fails.

---

## 7. make asan

```make
asan: CXXFLAGS += -fsanitize=address -fsanitize=undefined
asan: clean all
```

Two rules for one target:

- The first appends the sanitizer flags, **only** when the goal is `asan`. A
  plain `make` never sees them.
- The second forces `clean` before `all`. Without it, make would see an
  up-to-date binary, skip the compile, and leave the **un-instrumented** build
  running while you believed it was checked.

### What the flags do

The compiler rewrites the program, inserting a check before every memory access
and every operation that could be undefined. It also replaces `new`/`delete`
with versions that pad allocations with poisoned redzones and quarantine freed
memory instead of reusing it.

The program then **crashes loudly at the exact moment of the bug**, instead of
corrupting memory silently and misbehaving somewhere unrelated later.

### What it catches on this Mac

| Bug | Caught | Line numbers |
| --- | ------ | ------------ |
| Use after free | Yes | No — see below |
| Double free | Yes | No |
| Heap buffer overflow | Yes | No |
| Stack buffer overflow | Yes | No |
| Undefined behaviour (UBSan) | Yes | **Yes** |
| **Memory leaks** | **No** | — |

### Memory leaks are NOT detected here

**LeakSanitizer is not supported on macOS arm64.**

```
$ ASAN_OPTIONS=detect_leaks=1 ./program
AddressSanitizer: detect_leaks is not supported on this platform.
```

It works on Linux and on Intel Macs. On this machine, forgetting `destroy(head)`
will not be reported. The `destroy()` calls still matter — there is just no
automated check for them.

### Why ASan output has no line numbers

`llvm-symbolizer` is not installed. It ships with full Xcode, not with the
Command Line Tools:

```
$ xcrun -f llvm-symbolizer
xcrun: error: unable to find utility "llvm-symbolizer"
```

So ASan prints addresses and offsets rather than `file:line`. The report still
names three useful things: where the memory was touched, where it was freed,
and where it was allocated.

**UBSan is unaffected** and prints exact source locations:

```
ub.cpp:4:15: runtime error: shift exponent 40 is too large for 32-bit type 'int'
SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior ub.cpp:4:15
```

### Cost

Roughly 2x slower and 3x more memory. Irrelevant for practice programs, which
is why it is a separate target rather than always on.

### When to use it

Run `make asan` whenever the program does something inexplicable: a garbage
value, an intermittent crash, output that changes between runs. Those are the
signatures of touching freed or uninitialised memory.

---

## 8. Debugging a Makefile

```bash
make -n              # dry run: print the commands, execute nothing
make -B              # force a rebuild of everything, ignore timestamps
make --debug=b       # explain WHY each target was or was not rebuilt
make -p              # dump every rule and variable, including built-ins
make -j4             # run 4 recipes in parallel
```

`make -n` first, always. It shows exactly what would run with all variables
expanded, which instantly exposes a mistyped flag or an empty variable.

`make --debug=b` answers "why didn't it rebuild?"

---

## 9. The Android Build System

Android's build files use GNU Make syntax, so the fundamentals from the previous
sections carry over directly. What changes is the **role** the file plays.

### 9.1 Three different things get called "the Android build"

They are routinely confused. They are not the same system.

| | Who uses it | File | Built by |
| --- | --- | --- | --- |
| **NDK build** | App developers compiling native C/C++ into an APK | `Android.mk` + `Application.mk`, or `CMakeLists.txt` | `ndk-build` or CMake |
| **AOSP platform, legacy** | Platform/OS developers, older code | `Android.mk` | Kati → Ninja |
| **AOSP platform, current** | Platform/OS developers, current code | `Android.bp` | Soong → Ninja |

The `Android.mk` of the NDK and the `Android.mk` of the old AOSP tree share a
syntax and a name but are read by completely different build systems with
different variable sets. Note which world a tutorial is describing.

---

### 9.2 Android.mk — the NDK build

A minimal one:

```make
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := hello
LOCAL_SRC_FILES := hello.cpp
LOCAL_CPPFLAGS  := -std=c++17

include $(BUILD_SHARED_LIBRARY)
```

**There are no targets, no `:` rules, and no TAB-indented recipes.** Nothing in
this file describes *how* to compile anything.

Instead you set `LOCAL_*` variables and then `include` a script the NDK
provides. That script reads your variables and generates the real rules —
cross-compiler paths, sysroot, ABI flags, `.so` packaging, all of it.

You are filling in a form. `ndk-build` writes the Makefile.

#### The required skeleton

| Line | Why it is mandatory |
| ---- | ------------------- |
| `LOCAL_PATH := $(call my-dir)` | Must be first. `my-dir` is an NDK function returning the directory of this file, so sources can be named relatively |
| `include $(CLEAR_VARS)` | Resets every `LOCAL_*` variable. Required before **each** module, because one file may define several and they would otherwise leak into each other |
| `include $(BUILD_*)` | Must be last for the module. This is what actually generates the rules |

`CLEAR_VARS` deliberately does **not** clear `LOCAL_PATH` — that is the one
variable meant to persist across modules in a file.

#### Common LOCAL_ variables

| Variable | Sets |
| -------- | ----- |
| `LOCAL_MODULE` | Module name. `hello` produces `libhello.so` |
| `LOCAL_SRC_FILES` | Source files, relative to `LOCAL_PATH` |
| `LOCAL_C_INCLUDES` | Header search paths |
| `LOCAL_CFLAGS` | Flags for C **and** C++ |
| `LOCAL_CPPFLAGS` | Flags for C++ only |
| `LOCAL_LDFLAGS` | Linker flags |
| `LOCAL_LDLIBS` | System libraries, e.g. `-llog -landroid` |
| `LOCAL_STATIC_LIBRARIES` | Static modules to link |
| `LOCAL_SHARED_LIBRARIES` | Shared modules to link |
| `LOCAL_EXPORT_C_INCLUDES` | Include paths passed on to anything that depends on this module |

#### The BUILD_ scripts

| Include | Produces |
| ------- | -------- |
| `$(BUILD_SHARED_LIBRARY)` | `lib<name>.so` — the usual choice for an APK |
| `$(BUILD_STATIC_LIBRARY)` | `lib<name>.a` — linked into others, not packaged |
| `$(BUILD_EXECUTABLE)` | A command-line binary |
| `$(PREBUILT_SHARED_LIBRARY)` | Wraps an existing `.so` as a module |

#### Several modules in one file

This is why `CLEAR_VARS` exists:

```make
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := mathutils
LOCAL_SRC_FILES := math.cpp
include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE           := hello
LOCAL_SRC_FILES        := hello.cpp
LOCAL_STATIC_LIBRARIES := mathutils
LOCAL_LDLIBS           := -llog
include $(BUILD_SHARED_LIBRARY)
```

#### Application.mk

A companion file for project-wide settings, not per-module ones:

```make
APP_ABI      := arm64-v8a armeabi-v7a x86_64
APP_PLATFORM := android-24
APP_STL      := c++_shared
APP_OPTIM    := release
APP_CPPFLAGS := -std=c++17
```

| Variable | Sets |
| -------- | ----- |
| `APP_ABI` | Which CPU architectures to build. `all` builds every supported one |
| `APP_PLATFORM` | Minimum Android API level |
| `APP_STL` | Which C++ standard library — `c++_shared`, `c++_static`, or `none` |
| `APP_OPTIM` | `release` or `debug` |

`APP_ABI` is the reason one build produces several binaries: the whole build
runs once per architecture, into `libs/<abi>/`.

#### Running it

```bash
ndk-build                    # from the folder containing jni/Android.mk
ndk-build -j8 NDK_DEBUG=1    # parallel, debug build
ndk-build clean
```

#### Status

**`Android.mk` is legacy.** Google recommends **CMake** for new NDK projects,
and Android Studio defaults to it. `Android.mk` still works and a lot of
existing code uses it, but new native Android code should use
`CMakeLists.txt`.

---

### 9.3 Android.bp — Soong

Around Android 7–8, the AOSP platform build moved off `Android.mk` to
`Android.bp`.

The reason: `Android.mk` files are **programs**. They can contain conditionals,
loops, shell invocations and recursive variable expansion, which means the only
way to know what a build does is to run it. At AOSP's scale that made builds
slow, unpredictable, and nearly impossible to analyse statically.

`Android.bp` is the opposite. It is **pure declarative data** — deliberately not
a scripting language.

```blueprint
cc_binary {
    name: "hello",
    srcs: ["hello.cpp"],
    shared_libs: ["liblog"],
    cflags: ["-Wall", "-Werror"],
}
```

The syntax is JSON-like: `module_type { property: value, ... }`. Strings are
double-quoted, lists use `[]`, maps use `{}`, and **trailing commas are
required**.

#### What it deliberately cannot do

| Not supported | Why |
| ------------- | --- |
| `if` / conditionals | Would make the file unanalysable |
| Loops | Same |
| Arithmetic | Same |
| Shell commands | Same |
| Arbitrary variables | Only simple local assignment is allowed |

Anything genuinely needing logic goes into a **Soong plugin written in Go**, or
uses `soong_config_variables`. This is a constraint by design, not an omission.

#### Common module types

| Type | Produces |
| ---- | -------- |
| `cc_binary` | Native executable |
| `cc_library` | Both shared and static variants |
| `cc_library_shared` | `.so` only |
| `cc_library_static` | `.a` only |
| `cc_library_headers` | Headers only, no code |
| `cc_test` | A native test |
| `java_library` | A `.jar` |
| `android_app` | An APK |
| `android_library` | An AAR |
| `filegroup` | A named set of files usable by other modules |
| `genrule` | Generate files by running a tool |
| `cc_defaults` | A reusable block of properties — not a build output |
| `prebuilt_etc` | Install a prebuilt file |

#### Common properties

| Property | Means |
| -------- | ----- |
| `name` | Unique across the whole tree. Required |
| `srcs` | Source files. Supports globs like `["src/**/*.cpp"]` |
| `exclude_srcs` | Remove files matched by a glob |
| `shared_libs` | Shared libraries to link |
| `static_libs` | Static libraries to link |
| `header_libs` | Header-only dependencies |
| `include_dirs` | Include paths — absolute from the tree root |
| `local_include_dirs` | Include paths relative to this `Android.bp` |
| `export_include_dirs` | Include paths passed on to dependents |
| `cflags` | Compiler flags |
| `defaults` | Inherit from a `cc_defaults` module |
| `host_supported` | Also build for the host machine |
| `vendor` / `product` | Which partition it installs to |

#### Reuse with cc_defaults

There are no variables, so shared settings use a `cc_defaults` module:

```blueprint
cc_defaults {
    name: "my_defaults",
    cflags: [
        "-Wall",
        "-Werror",
        "-std=c++17",
    ],
    shared_libs: ["liblog"],
}

cc_binary {
    name: "hello",
    defaults: ["my_defaults"],
    srcs: ["hello.cpp"],
}

cc_library_shared {
    name: "libgreet",
    defaults: ["my_defaults"],
    srcs: ["greet.cpp"],
    export_include_dirs: ["include"],
}
```

#### Per-architecture and per-target settings

Instead of conditionals, `Android.bp` uses nested property blocks:

```blueprint
cc_library_shared {
    name: "libexample",
    srcs: ["common.cpp"],

    arch: {
        arm64: {
            srcs: ["arm64_impl.cpp"],
            cflags: ["-DARM64"],
        },
        x86_64: {
            srcs: ["x86_impl.cpp"],
        },
    },

    target: {
        android: {
            shared_libs: ["liblog"],
        },
        host: {
            cflags: ["-DHOST_BUILD"],
        },
    },
}
```

Soong merges the matching blocks into the base properties. Declarative, and
still statically analysable.

#### Tooling

```bash
bpfmt -w Android.bp          # canonical formatter. Run before committing
androidmk Android.mk > Android.bp   # convert legacy .mk (partial, needs review)
```

`androidmk` handles simple files. Anything using conditionals or shell will need
manual work, because those concepts do not exist in `Android.bp`.

---

### 9.4 How the pieces fit together

Neither Soong nor Kati compiles anything. Both are **generators** — they emit
Ninja files, and Ninja does the work.

```
     Android.bp                    Android.mk
    (Soong modules)             (legacy + product config)
         |                              |
         v                              v
    +---------+                    +---------+
    |  Soong  |                    |  Kati   |
    | (Go)    |                    | (C++)   |
    +---------+                    +---------+
         |                              |
         +--------------+---------------+
                        v
                   build.ninja
                        |
                        v
                    +-------+
                    | Ninja |     <-- actually runs the compiler
                    +-------+
                        |
                        v
                      out/
```

| Piece | Is |
| ----- | -- |
| **Blueprint** | The file *format* and its parser. A generic library, not Android-specific |
| **Soong** | The Android-specific build system built on Blueprint. Written in Go. Turns `Android.bp` into Ninja |
| **Kati** | A Google tool that converts remaining `Android.mk` — mostly product configuration — into Ninja instead of running GNU Make |
| **Ninja** | A deliberately dumb, very fast executor. Does not parse logic; just runs a precomputed dependency graph |
| **soong_ui** | The orchestrator invoked by `m`. Runs Kati and Soong, merges the output, then calls Ninja |

The design principle: put all the logic in the **generation** step, so the
**execution** step is a flat graph that parallelises perfectly. That is why
Ninja is fast, and why `Android.bp` is not allowed to contain logic.

Product configuration (`BoardConfig.mk`, `device.mk`, the `AndroidProducts.mk`
files) is **still GNU Make** — that part has not migrated, which is why Kati
still exists.

---

### 9.5 Building AOSP

```bash
source build/envsetup.sh     # adds lunch, m, mm, mmm to the shell
lunch aosp_arm64-eng         # pick target: <product>-<variant>
m -j16                       # build everything from the tree root
```

| Command | Does |
| ------- | ---- |
| `m` | Build the whole tree, from anywhere |
| `mm` | Build only the module in the current directory |
| `mmm <path>` | Build the module at that path |
| `mma` | Build the current module **and** its dependencies |
| `m <module>` | Build one named module |
| `m clean` | Remove `out/` |

Build variants: `eng` (development, extra debugging), `userdebug` (like a
release build but rootable), `user` (what ships).

Everything lands in `out/` — nothing is written next to the source. Same
principle as the `build/` habit in [section 1](#1-the-build-habit), at a scale
of hundreds of thousands of files.

> A note on Bazel: Google announced a long-term plan to move AOSP to Bazel. It
> has seen limited adoption and the timeline has shifted repeatedly, so treat
> any claim about its current status as needing verification against the AOSP
> documentation.

---

### 9.6 Side by side

| | Your Makefile | Android.mk (NDK) | Android.bp |
| --- | --- | --- | --- |
| Language | GNU Make | GNU Make | Blueprint (declarative) |
| You write | Rules and recipes | Variable assignments | Module declarations |
| Rules come from | You | NDK scripts | Soong |
| Logic allowed | Yes | Yes | **No** |
| TAB-indented recipes | Required | None | None |
| Runs the compiler | make | make | Ninja |
| Command | `make` | `ndk-build` | `m` |
| Targets built | This Mac, arm64 | Every ABI in `APP_ABI` | Whole device image |
| Status | Current | Legacy — use CMake | Current for AOSP |

### 9.7 What transfers

From the earlier sections, the portable parts are `:=`, `$(VAR)`, `include`, and
the dependency-graph model. They appear in `Android.mk`, in kernel builds, and in
most C/C++ projects on Linux.

The part `Android.mk` and `Android.bp` both hide is the half you actually write
in [section 5](#5-the-makefile) — your own targets, prerequisites and recipes.
That is the more valuable half to understand, because it is exactly what
ndk-build, Soong, Kati and CMake all generate underneath.

---

## 10. Common Errors

| Error | Cause |
| ----- | ----- |
| `missing separator. Stop.` | Spaces instead of a TAB on a recipe line. Verify with `awk '/^\t/{n++} END{print n+0}' Makefile` |
| `grep: invalid option -- P` | macOS ships BSD grep. Use the `awk` command above instead |
| `No targets specified and no makefile found` | Wrong folder, or the file is named `makefile.txt`. Must be exactly `Makefile` or `makefile` |
| `Nothing to be done for 'all'` | Not an error. Nothing changed since the last build |
| Edits appear to be ignored | Ran the old binary because the build failed, or a header changed that make does not track. Confirm with `make clean && make` |
| `build/` shows in `git status` | `.gitignore` is not at the repo root, or was saved as `gitignore` without the dot |
| Binary still tracked after ignoring | It was already committed. Use `git rm --cached` |
| `command not found: ./build/...` | Missing `./`, or the build failed and the binary was never created |
| `make: ./build/: Permission denied` | Using the old `run: $(BUILD)/$(F)` form without `F=`. `$(F)` expanded to nothing so the recipe tried to execute the `build/` **directory**. Switch to the `run-%` rule |
| `No rule to make target 'run-foo'` | No `foo.cpp` in the folder. Run `make list` to see the real names |
| `cd` in a recipe has no effect | Each recipe line is a separate shell. Chain with `&&` |

---

## 11. Quick Reference

```bash
# Daily use
make                       # build everything changed
make list                  # show available program names
make run-linked_list       # build and run one program
make asan                  # rebuild with the sanitizers
make clean                 # delete build/

# Debugging the build
make -n                    # dry run
make -B                    # force full rebuild
make --debug=b             # why did/didn't it rebuild

# Without a Makefile
mkdir -p build && g++ -std=c++17 -Wall -Wextra -g linked_list.cpp -o build/linked_list && ./build/linked_list

# Checking tabs
awk '/^\t/{n++} END{print n+0}' Makefile     # expect 5
cat -t Makefile                              # tabs show as ^I

# Git
git status --untracked-files=all             # see inside new folders
git check-ignore -v <path>                   # which rule ignored it
git rm --cached <file>                       # untrack an already-committed binary
```

### Android

```bash
# NDK (Android.mk)
ndk-build                                    # build from jni/Android.mk
ndk-build -j8 NDK_DEBUG=1
ndk-build clean

# AOSP (Android.bp)
source build/envsetup.sh                     # adds lunch, m, mm, mmm
lunch aosp_arm64-eng                         # <product>-<variant>
m -j16                                       # build the whole tree
mm                                           # build only this directory's module
m <module>                                   # build one named module

# Android.bp tooling
bpfmt -w Android.bp                          # format before committing
androidmk Android.mk > Android.bp            # convert legacy (partial)
```

### Automatic variables

| `$@` | `$<` | `$^` | `$*` |
| ---- | ---- | ---- | ---- |
| target | first prerequisite | all prerequisites | the `%` stem |

### New project folder

1. `mkdir MALIKH_CODES/NewTopic && cd MALIKH_CODES/NewTopic`
2. Copy the [Makefile](#the-file) into it, unchanged
3. Verify the tabs: `awk '/^\t/{n++} END{print n+0}' Makefile` → 5
4. Write the `.cpp`, then `make && make run-<name>`

The root `.gitignore` already covers the new `build/` folder. Nothing to add.
