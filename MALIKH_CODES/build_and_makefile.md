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
4. [The Makefile](#4-the-makefile)
5. [Common Errors](#5-common-errors)
6. [Quick Reference](#6-quick-reference)

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

If `build/` still appears, either the file is not at the repo root, or VS Code
saved it as `gitignore` without the leading dot.

Check a single file and see which rule caught it:

```bash
git check-ignore -v MALIKH_CODES/Linked_List/build/linked_list
```

Prints the `.gitignore` line responsible. Prints nothing if it is not ignored.

Then commit:

```bash
git add .
git status                                  # read this before committing
git commit -m "Add .gitignore, move binaries to build/"
git push
```

---

## 4. The Makefile

`make` ships with the Command Line Tools, so it is already installed.

A `Makefile` records the build recipe once, so `-std=c++17` can never be
forgotten and a collaborator can build without asking which flags to use. It
also skips work that is not needed — make compares timestamps and will not
recompile a `.cpp` that has not changed.

The `Makefile` **is source code**. Commit it.

### The TAB rule

**Recipe lines must begin with a literal TAB character. Not spaces.**

Spaces produce an error that explains nothing:

```
Makefile:8: *** missing separator.  Stop.
```

VS Code converts tabs to spaces by default. Fix before saving:

- Status bar, bottom right → click **"Spaces: 4"** → **Indent Using Tabs**
- Or in `settings.json`:

```json
"[makefile]": { "editor.insertSpaces": false }
```

This is the most common Makefile problem. Check it first, always.

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

### Reading it

| Piece | Means |
| ----- | ----- |
| `CXX := g++` | A variable. Used later as `$(CXX)` |
| `all: $(BINS)` | The **first** target is the default, so bare `make` runs this |
| indented line | The recipe — the shell command. Starts with a **TAB** |
| `$(wildcard *.cpp)` | Every `.cpp` in the folder |
| `$(patsubst %.cpp,$(BUILD)/%,...)` | Turns `linked_list.cpp` into `build/linked_list` |
| `$(BUILD)/%: %.cpp` | A **pattern rule** — one recipe covering all files |
| `$<` | The first prerequisite (the `.cpp`) |
| `$@` | The target (the binary) |
| `\| $(BUILD)` | Order-only prerequisite. Create the folder first, but do not rebuild just because its timestamp changed |
| `asan: CXXFLAGS += ...` | Target-specific variable — extra flags for this target only |
| `.PHONY` | These are command names, not files. Without it, if a file named `clean` ever exists, `make clean` silently does nothing |

### Usage

```bash
make                       # build every .cpp in the folder
make run F=linked_list     # build and run one program
make asan                  # rebuild everything with the memory checker
make clean                 # delete build/
```

**`make asan` is the important one for linked list work.** Linked lists are all
raw `new`/`delete`, and AddressSanitizer reports leaked nodes and use-after-free
with exact line numbers — instead of a silent wrong answer or a bare
`Segmentation fault`.

Running `make` twice in a row prints `Nothing to be done for 'all'`. That is not
an error, it means nothing changed. Force a full rebuild with
`make clean && make`.

---

## 5. Common Errors

| Error | Cause |
| ----- | ----- |
| `missing separator. Stop.` | Spaces instead of a TAB on a recipe line |
| `No targets specified and no makefile found` | Wrong folder, or the file is named `makefile.txt`. Must be exactly `Makefile` or `makefile` |
| `Nothing to be done for 'all'` | Not an error. Nothing changed since the last build |
| `build/` shows in `git status` | `.gitignore` is not at the repo root, or was saved as `gitignore` without the dot |
| Binary still tracked after ignoring | It was already committed. Use `git rm --cached` |
| `command not found: ./build/linked_list` | Missing `./`, or the build failed and the binary was never created |

---

## 6. Quick Reference

```bash
# Daily use
make                       # build everything changed
make run F=linked_list     # build and run one program
make asan                  # rebuild with memory checking
make clean                 # delete build/

# Without a Makefile
mkdir -p build && g++ -std=c++17 -Wall -Wextra -g linked_list.cpp -o build/linked_list && ./build/linked_list

# Git
git status                                          # build/ should NOT appear
git check-ignore -v <path>                          # which rule ignored it
git rm --cached <file>                              # untrack an already-committed binary
```

### New project folder

1. `mkdir MALIKH_CODES/NewTopic && cd MALIKH_CODES/NewTopic`
2. Copy the [Makefile](#the-file) into it
3. Confirm VS Code is set to tabs for Makefiles
4. Write the `.cpp`, then `make && make run F=<name>`

The root `.gitignore` already covers the new `build/` folder. Nothing to add.
