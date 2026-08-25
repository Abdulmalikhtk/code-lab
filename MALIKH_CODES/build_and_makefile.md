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
9. [Common Errors](#9-common-errors)
10. [Quick Reference](#10-quick-reference)

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

Must print **4** for the Makefile below.

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

run: $(BUILD)/$(F)
	./$(BUILD)/$(F)

asan: CXXFLAGS += -fsanitize=address -fsanitize=undefined
asan: clean all

clean:
	rm -rf $(BUILD)

.PHONY: all run asan clean
```

The same file works unchanged in every project folder. Copy it as-is.

### Line by line

| Line | Does |
| ---- | ---- |
| `CXX := g++` | Variable. Change the compiler in one place |
| `SRCS := $(wildcard *.cpp)` | Every `.cpp` in the folder → `linked_list.cpp` |
| `BINS := $(patsubst ...)` | Turns that into `build/linked_list` |
| `all: $(BINS)` | The **default goal** — the first target is what bare `make` builds. No recipe; it just depends on every binary |
| `$(BUILD)/%: %.cpp` | The engine. A **pattern rule** covering every program in the folder |
| `$(BUILD):` | A rule whose target is a **directory**. Runs once |
| `run: $(BUILD)/$(F)` | `F` comes from the command line. Depends on the binary, so it builds first |
| `asan: CXXFLAGS += ...` | Appends flags **only** when the goal is `asan` |
| `asan: clean all` | Two rules, one target. Forces a clean rebuild |
| `clean:` | `rm -rf build` |
| `.PHONY:` | Marks command-targets so make does not treat them as filenames |

### Usage

```bash
make                       # build every .cpp in the folder
make run F=linked_list     # build and run one program
make asan                  # rebuild with the sanitizers
make clean                 # delete build/
```

Force a full rebuild: `make clean && make`, or `make -B`.

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

## 9. Common Errors

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
| `cd` in a recipe has no effect | Each recipe line is a separate shell. Chain with `&&` |

---

## 10. Quick Reference

```bash
# Daily use
make                       # build everything changed
make run F=linked_list     # build and run one program
make asan                  # rebuild with the sanitizers
make clean                 # delete build/

# Debugging the build
make -n                    # dry run
make -B                    # force full rebuild
make --debug=b             # why did/didn't it rebuild

# Without a Makefile
mkdir -p build && g++ -std=c++17 -Wall -Wextra -g linked_list.cpp -o build/linked_list && ./build/linked_list

# Checking tabs
awk '/^\t/{n++} END{print n+0}' Makefile     # expect 4
cat -t Makefile                              # tabs show as ^I

# Git
git status --untracked-files=all             # see inside new folders
git check-ignore -v <path>                   # which rule ignored it
git rm --cached <file>                       # untrack an already-committed binary
```

### Automatic variables

| `$@` | `$<` | `$^` | `$*` |
| ---- | ---- | ---- | ---- |
| target | first prerequisite | all prerequisites | the `%` stem |

### New project folder

1. `mkdir MALIKH_CODES/NewTopic && cd MALIKH_CODES/NewTopic`
2. Copy the [Makefile](#the-file) into it, unchanged
3. Verify the tabs: `awk '/^\t/{n++} END{print n+0}' Makefile` → 4
4. Write the `.cpp`, then `make && make run F=<name>`

The root `.gitignore` already covers the new `build/` folder. Nothing to add.
