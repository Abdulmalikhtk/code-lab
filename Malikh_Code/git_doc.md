# Git — Working Notes

Personal reference for the `code-lab` repo.

```
Repo root   ~/coding_practise/CODE_PRACTICE
Remote      github.com/Abdulmalikhtk/code-lab
Branch      main
Identity    abdulmalikhtk@gmail.com   (repo-local, overrides work email)
```

---

## Contents

1. [Mental Model](#1-mental-model)
2. [One-Time Setup](#2-one-time-setup)
3. [Gitignore](#3-gitignore)
4. [First Push](#4-first-push)
5. [Daily Loop](#5-daily-loop)
6. [Staging](#6-staging)
7. [Reading Git Status](#7-reading-git-status)
8. [Git Diff](#8-git-diff)
9. [Undo](#9-undo)
10. [Checkout and Switch](#10-checkout-and-switch)
11. [Pager](#11-pager)
12. [Cheat Sheet](#12-cheat-sheet)

---

## 1. Mental Model

A file lives in one of three places, not two.

```
  working tree          staging             history            GitHub
  (my files)   ------>  (index)   ------>   (.git/)   ------>  (remote)
                git add           git commit         git push
```

| Place        | What it is                      |
| ------------ | ------------------------------- |
| working tree | The files I actually edit       |
| staging      | A draft of the next commit      |
| history      | Permanent, immutable snapshots  |

Staging looks like bureaucracy and isn't. It is what lets me edit eight files
and commit only three of them as one coherent change.

---

## 2. One-Time Setup

### Create the repo

```bash
git init -b main
```

- Creates `.git/`. That folder is the repository.
- Source files are not moved or copied, just watched.
- Delete `.git` and it is plain files again, no history.
- `-b main` because git still defaults to `master`, which warns and mismatches GitHub.

### Set identity for this repo only

```bash
git config user.email "abdulmalikhtk@gmail.com"
git config user.name  "Abdul Malikh T K"

git config user.email          # verify
```

No `--global`. Without the flag it writes to `.git/config` and affects this repo
only. With it, it writes to `~/.gitconfig` and affects everything.

This matters here: the global identity is `tkabdulmalikh@meta.com`. Without the
override, every personal commit gets stamped with the work email, permanently.

### Connect to GitHub

On github.com choose **New repository**. Do not tick "Add a README" or
"Add .gitignore" — the repo must be empty, or its commit conflicts with mine on
the first push.

```bash
git remote add origin https://github.com/Abdulmalikhtk/code-lab.git

git remote -v                  # verify
```

---

## 3. Gitignore

Write this before the first `git add`.

**Rule: commit sources, never build outputs.**

```gitignore
# Compiled object files and binaries
*.o
*.out
*.exe
*.app

# macOS debug symbol bundles
*.dSYM/

# Executables from our projects
demo
demo_asan

# Never ignore source, no matter what matched above
!*.cpp
!*.h
!*.md

# macOS clutter
.DS_Store
```

### Pattern rules

| Pattern         | Matches                                    |
| --------------- | ------------------------------------------ |
| `*.o`           | That extension, at any depth               |
| `*.dSYM/`       | Trailing slash means directories only      |
| `demo`          | A file named exactly that, in any directory |
| `build/**/*.o`  | `**` spans any depth in between            |
| `[0-9][0-9]`    | Character class, here two digits           |
| `!*.cpp`        | Negation, "never ignore these"             |

**Negation gotcha.** `!` cannot rescue a file inside an ignored directory. Git
never descends into an excluded folder, so it never sees the file to reconsider
it. Add `build/` and `!build/notes.md` will not work.

### Why binaries are never committed

| Reason        | Detail                                                                 |
| ------------- | ---------------------------------------------------------------------- |
| Bloat         | `demo` is 93 KB, its source is 4 KB. Binaries do not diff or compress, and git keeps every version forever. |
| False changes | Recompile without editing and the binary still differs. `git status` becomes permanent noise, so I stop reading it. |
| Conflicts     | Two people compile, both binaries differ, git cannot merge them. Nobody resolves a conflict in machine code. |
| Wrong arch    | `demo` is arm64 Mac. Useless on Linux or Intel.                        |

**Best habit.** Put binaries in `build/` and ignore one line, forever.

---

## 4. First Push

```bash
git add .
git status                                      # read this before committing
git commit -m "Initial commit: C++ practice"
git push -u origin main
```

### What -u does

`-u` is short for `--set-upstream`. It writes a permanent note in `.git/config`.

```ini
[branch "main"]
    remote = origin
    merge = refs/heads/main
```

Without it, a bare `git push` does not know where to go. With it:

```bash
git push        # knows: origin, main
git pull        # knows where to pull from
git status      # can now say "ahead of origin/main by 2 commits"
```

Pass `-u` once per branch, not once per repo.

### Auth

GitHub rejects the account password over HTTPS. Use a Personal Access Token:

```
Settings -> Developer settings -> Personal access tokens -> Fine-grained
Permission needed: Contents: read and write
```

Paste the token at the password prompt. SSH keys are the set-up-once alternative.

---

## 5. Daily Loop

```bash
git status                                      # what changed?
git add linked_list.cpp                         # or: git add .
git commit -m "Add reverse() to linked list"
git push
```

Four commands. That is the whole job.

---

## 6. Staging

### Ways to stage

```bash
git add file.cpp        # one file
git add cpp_basics/     # a whole folder
git add "*.cpp"         # every .cpp anywhere (quotes matter)
git add .               # everything not ignored, be careful
git add -p file.cpp     # interactively pick chunks within a file
```

`git add .` grabs everything. This is where `.gitignore` earns its keep.

`git add -p` is worth learning early. It walks the file chunk by chunk asking
include or not, which is how I commit a bug fix without dragging in the
half-finished experiment three lines below.

### The edit-after-staging trap

`git add` snapshots the file as it is at that moment. Edit it afterwards and the
commit saves the old version.

Fix: run `git add` again. Re-adding overwrites the previous snapshot.

```bash
git add .
# ... edit main.cpp ...
git add .                       # re-stage, now the new edits are included
git commit -m "..."
```

### Shortcut

```bash
git commit -am "message"
```

`-a` auto-stages every tracked file that changed. It does not pick up new files
git has never seen.

---

## 7. Reading Git Status

`git status --short` prints two characters before each filename. They are two
independent answers, one per gap in the three-place model.

```
  history  <--[ col 1 ]--  staging  <--[ col 2 ]--  working tree

  X Y  filename
  | |
  | +-- col 2:  disk vs staging       "changed since I staged"
  +---- col 1:  staging vs commit     "what is ready to commit"
```

### Letters

| Letter    | Meaning                                  |
| --------- | ---------------------------------------- |
| `A`       | Added, new file git had never seen       |
| `M`       | Modified                                 |
| `D`       | Deleted                                  |
| `R`       | Renamed                                  |
| `?`       | Untracked                                |
| *(space)* | No change in this position               |

### Decoding the codes

| Code | Column 1      | Column 2       | Means                                                                 |
| ---- | ------------- | -------------- | --------------------------------------------------------------------- |
| `A ` | staged as new | —              | Clean. Staged version matches disk.                                    |
| `AM` | staged as new | edited since   | Two versions exist. Committing now saves the staged one and drops the newer edits. Re-add. |
| ` M` | —             | modified       | Normal state after editing. Committing now saves nothing for this file. |
| `??` | —             | —              | Untracked. Git has no record at all, invisible until `git add`.         |
| `AD` | staged as new | deleted        | Ghost entry: staged, then deleted or renamed. Clear with `git rm --cached`. |

Note the leading space in ` M`. The columns are positional.

### Scanning by column

```
anything in column 2   ->  not saved yet, needs git add
column 1 only          ->  staged and current, ready to commit
both columns           ->  two versions exist, almost always means re-add
??                     ->  invisible to git entirely
```

### Long form says the same thing

| Short form         | Long-form section              |
| ------------------ | ------------------------------ |
| col 1 has a letter | Changes to be committed        |
| col 2 has a letter | Changes not staged for commit  |
| `??`               | Untracked files                |

Which is why an `AM` file appears twice in long form, once in each section.

---

## 8. Git Diff

One question: which two snapshots?

```
  working tree  <--(1)-->  staging  <--(2)-->  last commit
                <-------------(3)------------>
```

```bash
git diff              # (1) unstaged edits, what I would MISS if I commit now
git diff --cached     # (2) staged changes, what I WILL commit
git diff HEAD         # (3) everything uncommitted, staged or not
```

Those three cover 90% of use. `--staged` is a synonym for `--cached`.

If `git diff` prints nothing, staging matches my files and it is safe to commit.

### Scoping

```bash
git diff f.cpp                 # one file
git diff linked_list/          # one folder
git diff --stat                # summary only: files changed, +/- counts
git diff --name-only           # just filenames
```

### Commits and branches

`HEAD` is the current commit, `HEAD~1` the one before it.

```bash
git diff HEAD~1 HEAD           # what the last commit changed
git diff HEAD~3                # everything since 3 commits ago
git diff main feature-x        # two branches
git diff a3f9c21 b7e2d10       # two commits by hash
git diff main..origin/main     # local vs remote, what I have not pulled
```

### Readability

```bash
git diff --word-diff           # highlight changed words, not whole lines
git diff -w                    # ignore whitespace-only changes
```

`-w` earns its keep in C++ when reindenting a block makes 200 lines of nothing.

---

## 9. Undo

**`git restore` cannot touch committed work.** It overwrites unsaved edits using
a saved version. Commits are never modified. The only thing at risk is work that
exists nowhere but the editor.

### The default source is staging, not the last commit

Tested:

```
  committed = VERSION-1     staged = VERSION-2     on disk = VERSION-3

  git restore f.txt                 ->  VERSION-2    (from staging)
  git restore --source=HEAD f.txt   ->  VERSION-1    (from last commit)
  git log --oneline                 ->  unchanged, both times
```

So after a `git add`, `git restore` rewinds to that snapshot, not the last commit.

### --staged is the undo for git add

It takes a file out of staging without touching the file.

```bash
git add .                          # oops, grabbed everything

git status --short
#   A  main.cpp
#   A  notes.txt
#   A  secret.env                  <- did not mean to include this

git restore --staged secret.env

git status --short
#   A  main.cpp
#   A  notes.txt
#   ?? secret.env                  <- back to untracked, file still on disk
```

Safe because it edits only the middle box. Nothing to recover, just `git add` again.

### The one-character difference that matters

```bash
git restore --staged f.cpp    # unstage, edits survive      SAFE
git restore          f.cpp    # discard edits               IRREVERSIBLE
```

| Command                      | Destroys                | Safe?        |
| ---------------------------- | ----------------------- | ------------ |
| `git restore --staged f.cpp` | nothing, just unstages  | safe         |
| `git restore f.cpp`          | uncommitted edits       | irreversible |
| `git commit` / `git push`    | nothing                 | safe         |

Both at once: `git restore --staged --worktree f.cpp`. Rarely what I want.

**Habit.** Run `git diff f.cpp` before `git restore f.cpp`. It prints exactly
what is about to be thrown away.

---

## 10. Checkout and Switch

`checkout` historically did several unrelated jobs, hence the confusion. Git 2.23
(2019) split it. Learn the new commands, recognise the old ones.

### Job 1: switch branches, use git switch

```bash
git switch main               # move to an existing branch
git switch -c feature-x       # create a new branch and move to it
git switch -                  # jump back to previous branch
```

Old equivalents: `git checkout main`, `git checkout -b feature-x`.

Switching rewrites the folder to match that branch. Uncommitted changes block it.
Git refuses rather than clobber work.

### Job 2: restore files, use git restore

```bash
git restore f.cpp                    # discard uncommitted edits   IRREVERSIBLE
git restore --staged f.cpp           # unstage                     safe
git restore --source=HEAD~2 f.cpp    # pull an old version of one file
```

Old equivalents: `git checkout -- f.cpp`, `git reset HEAD f.cpp`.

### Job 3: inspect an old commit, still checkout

```bash
git checkout a3f9c21          # see the repo as it was then
git switch -                  # get back
```

This is detached HEAD. Not on a branch, and commits made here get orphaned. Fine
for looking, do not work there.

---

## 11. Pager

`git diff`, `git log` and `git show` pipe through `less` when output exceeds one
screen. **Press `q` to get out.**

| Key           | Does                        |
| ------------- | --------------------------- |
| `q`           | quit                        |
| `space` / `f` | page down                   |
| `b`           | page up                     |
| arrows        | line by line                |
| `/text`       | search, `n` for next hit    |
| `G`           | jump to end                 |

```bash
git config --global core.pager "less -FX"    # -F quit if it fits, -X keep in scrollback
git --no-pager diff                          # bypass once
```

---

## 12. Cheat Sheet

```bash
# Inspect
git status                      # what changed
git status --short              # compact, two-column
git log --oneline               # what I have committed
git diff                        # unstaged edits
git diff --cached               # what I am about to commit

# Save
git add .                       # stage everything not ignored
git commit -m "message"         # snapshot staging
git push                        # send to GitHub

# Undo
git restore --staged f.cpp      # unstage             safe
git restore f.cpp               # discard edits       IRREVERSIBLE
git rm --cached f.cpp           # drop a ghost index entry
git switch -                    # back to previous branch
```

**The rule that makes all of this low-stakes.** Once something is committed it is
very hard to lose. Git keeps a reflog even for commits I deleted. It is the
uncommitted work that is fragile, so commit early and often. History can be
tidied later.


--
after git push -u origin main

UI authentication link copy

https://github.com/login/device

git log --oneline     # should list your commit
git status            # should say "up to date with 'origin/main'"


Commits don't have names — pointers do
A commit is just a snapshot with a hash (e50f33e). It never moves and never changes. What moves are the labels pointing at it.

        e50f33e
           ▲
           │
    ┌──────┼──────┐
   main         origin/main
    ▲
    │
   HEAD

git log --oneline --all --graph    # every branch, drawn as a graph
git branch -a                      # local and remote branches
cat .git/HEAD                      # literally: ref: refs/heads/main
