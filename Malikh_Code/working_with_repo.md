# Working With the Shared Repo

Pulling, pushing, and getting unstuck when two people edit the same repository.

```
Repo          github.com/Abdulmalikhtk/code-lab
Local         ~/Downloads/Practice1/code-lab
Branch model  Everyone commits directly to main
Collaborators Abdulmalikhtk (Malikh_Code/), Aafren (Aafren_Code/)
```

Related: [get_started.md](get_started.md) for sharing the repo and pull
requests, [git_branch.md](git_branch.md) for branches,
[git_doc.md](git_doc.md) for `.gitignore` and first push.

---

## Contents

1. [Why Conflicts Keep Happening](#1-why-conflicts-keep-happening)
2. [The Daily Cycle](#2-the-daily-cycle)
3. [Reading git status](#3-reading-git-status)
4. [Pull Rejected: Local Changes](#4-pull-rejected-local-changes)
5. [Stash](#5-stash)
6. [Push Rejected](#6-push-rejected)
7. [Merge Conflicts](#7-merge-conflicts)
8. [Modify/Delete Conflicts](#8-modifydelete-conflicts)
9. [Worked Example: The Folder Rename](#9-worked-example-the-folder-rename)
10. [Undoing Things](#10-undoing-things)
11. [Rules of Thumb](#11-rules-of-thumb)
12. [Quick Reference](#12-quick-reference)

---

## 1. Why Conflicts Keep Happening

Two people, one branch, no coordination:

```
Abdulmalikhtk ──┐
                ├──> main ──> origin/main
Aafren ─────────┘
```

Both commit straight to `main`. Whoever pushes second has to reconcile with
whatever the first one did. There is no branch isolating the work, so every
session starts from a tree that may already have moved.

This is not a mistake — it is fine for a two-person practice repo. It just means
**pulling before you start is not optional.**

The single rule that prevents most of the pain:

> **`git pull` before you write anything. `git push` as soon as it works.**

Long gaps between pulls are what turn a two-line change into a merge conflict.

---

## 2. The Daily Cycle

```bash
cd ~/Downloads/Practice1/code-lab

git pull                    # FIRST. before opening any file

# ... edit, build, test ...

git add .
git status                  # read this before committing
git commit -m "what changed"
git push
```

That is the whole workflow when nothing goes wrong.

`git pull` is two operations: **fetch** (download the remote's commits) and
**merge** (combine them with yours). The merge step is where things break, and
it needs a clean working tree to run.

### Check before you start

```bash
git status                  # anything uncommitted from last time?
git log --oneline -5        # where am I?
git log --oneline -5 origin/main   # where is the remote?
```

---

## 3. Reading git status

`git status --short` prints two letters per file. Left column = **staged**,
right column = **working tree**.

| Code | Means |
| ---- | ----- |
| `M ` | Modified and **staged** |
| ` M` | Modified, **not staged** |
| `MM` | Staged, then modified again |
| `A ` | New file, staged |
| `??` | Untracked — git does not know about it |
| `D ` | Deleted, staged |
| `DU` | **Conflict** — deleted by us, modified by them |
| `UU` | **Conflict** — both modified |
| `AA` | **Conflict** — both added |

Any code containing `U` means **unmerged**: git stopped and is waiting for you.
You cannot commit until every `U` is resolved.

Git collapses whole new folders into one entry. To see inside:

```bash
git status --untracked-files=all
```

---

## 4. Pull Rejected: Local Changes

```
error: Your local changes to the following files would be overwritten by merge:
        Malikh_Code/Linked_List/mylinkedlist.cpp
        Malikh_Code/build_and_makefile.md
Please commit your changes or stash them before you merge.
Aborting
```

**Nothing happened.** Git refused to start rather than risk destroying work.
Your files are untouched.

The remote changed the same files you changed, and yours are not committed, so
there is no saved version to merge against.

### Three ways forward

| Option | Command | Keeps your work? |
| ------ | ------- | ---------------- |
| **Commit** | `git add . && git commit -m "..."` | Yes — best when the work is real |
| **Stash** | `git stash` | Yes, parked. Best when unsure |
| **Discard** | `git checkout -- <file>` | **No. Permanent** |

### Before discarding anything

`git checkout --` on uncommitted changes is **unrecoverable**. There is no undo,
no reflog entry, nothing. Check what you would lose first:

```bash
git diff <file>                     # what changed vs the last commit
git diff --stat                     # how much, across all files
wc -c <file>                        # current size
git show HEAD:<file> | wc -c        # size at the last commit
```

A large size difference means real work is sitting there uncommitted. This check
takes five seconds and has saved entire documents.

---

## 5. Stash

A stash is a shelf. It takes your uncommitted changes, saves them, and gives you
a clean tree.

```bash
git stash                   # park everything, tree goes clean
git pull                    # now the merge can run
git stash pop               # bring the changes back
```

| Command | Does |
| ------- | ---- |
| `git stash` | Save and clear the working tree |
| `git stash list` | Show what is stashed |
| `git stash show -p` | Show the full diff of the newest stash |
| `git stash pop` | Restore **and remove** from the stash |
| `git stash apply` | Restore but **keep** it stashed — safer |
| `git stash drop` | Delete the newest stash |
| `git stash -u` | Also stash untracked files |

### Two things to know

**`git stash pop` can conflict.** If the pull changed the same lines, popping
produces a conflict exactly like a merge. When that happens git **keeps the
stash entry** rather than deleting it, so nothing is lost:

```
The stash entry is kept in case you need it again.
```

**Do not `git stash drop` until you have verified the result.** Once the pop has
conflicted, that stash is your only remaining copy. Run `git status`, confirm the
files look right, commit — *then* drop.

`git stash apply` avoids the problem entirely: it restores without removing, so
you drop it deliberately once you are happy.

---

## 6. Push Rejected

```
! [rejected]        main -> main (fetch first)
error: failed to push some refs
hint: Updates were rejected because the remote contains work that you do not
hint: have locally.
```

Someone pushed while you were working. Pull, then push:

```bash
git pull
git push
```

If the pull produces conflicts, resolve them ([section 7](#7-merge-conflicts))
and then push.

**Never use `git push --force` on a shared branch.** It deletes the other
person's commits from the remote. There is no situation in this repo that calls
for it.

---

## 7. Merge Conflicts

When you and the remote changed **the same lines**, git cannot choose and writes
both versions into the file:

```
<<<<<<< HEAD
my version of the line
=======
their version of the line
>>>>>>> origin/main
```

### Resolving

1. Open the file. Find every `<<<<<<<` block.
2. Edit until the file reads correctly — keep yours, theirs, or a combination.
3. **Delete all three marker lines** (`<<<<<<<`, `=======`, `>>>>>>>`).
4. Stage it: `git add <file>`
5. Repeat for every conflicted file, then `git commit`.

```bash
git status              # list the conflicted files
git diff                # see the conflicts
# ...edit...
git add <file>
git commit              # message is pre-filled for a merge
```

Forgetting to delete the markers is the classic mistake — they are not comments,
and a `.cpp` full of `<<<<<<<` will not compile.

### Escape hatch

```bash
git merge --abort       # cancel the merge, back to before the pull
```

---

## 8. Modify/Delete Conflicts

A different, more confusing conflict:

```
CONFLICT (modify/delete): Malikh_Code/Linked_List/mylinkedlist.cpp
deleted in Updated upstream and modified in Stashed changes.
```

There are no `<<<<<<<` markers, because there is nothing to interleave. One side
deleted the file; the other edited it. Git cannot merge an edit into a deletion,
so it asks you to decide.

**The usual cause is a rename.** Git stores a rename as *delete the old path,
add the new one*. If you edited the file at the old path, your change now points
at a path that no longer exists.

### Resolving

**Keep the file** — copy it to wherever it now belongs, accept the deletion at
the old path:

```bash
cp old/path/file.cpp new/path/file.cpp
git rm old/path/file.cpp
git add new/path/file.cpp
```

**Discard it** — accept the deletion:

```bash
git rm old/path/file.cpp
```

Either way the `DU` clears and you can commit. If `git rm` refuses because the
path is unmerged, add `-f`.

---

## 9. Worked Example: The Folder Rename

A real incident from this repo, start to finish.

### What happened

Two files were modified locally and uncommitted. Meanwhile Aafren pushed a
commit that **renamed the top-level folders**:

```
MALIKH_CODES/  ->  Malikh_Code/
AAFREN_CODES/  ->  Aafren_Code/
                   preparing_plan/   (new)
```

### Step 1 — the pull refused

```
error: Your local changes to the following files would be overwritten by merge:
        MALIKH_CODES/Linked_List/mylinkedlist.cpp
        MALIKH_CODES/build_and_makefile.md
Aborting
```

### Step 2 — stash and pull

```bash
git stash
git pull
```

The pull fast-forwarded, and the folders were renamed on disk.

### Step 3 — the pop half-succeeded

```bash
git stash pop
```

```
CONFLICT (modify/delete): MALIKH_CODES/Linked_List/mylinkedlist.cpp
deleted in Updated upstream and modified in Stashed changes.

Changes to be committed:
        modified:   Malikh_Code/build_and_makefile.md
Unmerged paths:
        deleted by us:   MALIKH_CODES/Linked_List/mylinkedlist.cpp
```

Two different outcomes in one command:

- **`build_and_makefile.md` merged cleanly.** Git detected the rename and
  applied the edit at the *new* path automatically. No action needed.
- **`mylinkedlist.cpp` conflicted.** Git could not match it to a new path, so it
  left the old file on disk and marked it `DU`.

Rename detection is a heuristic based on content similarity. It worked for the
33 KB document and failed for the small, heavily-changed source file.

### Step 4 — resolve

```bash
cp MALIKH_CODES/Linked_List/mylinkedlist.cpp Malikh_Code/Linked_List/mylinkedlist.cpp
git rm MALIKH_CODES/Linked_List/mylinkedlist.cpp
git add Malikh_Code/Linked_List/mylinkedlist.cpp
git status                  # verify: no unmerged paths
```

### Step 5 — commit and clean up

```bash
git commit -m "Add Android build system section; keep notes after folder rename"
git stash drop
rm -rf MALIKH_CODES         # leftover old folder, build artifacts only
git push
```

### What made it recoverable

The stash. Had `git checkout --` been used at step 1, 15 KB of uncommitted
document would have been gone permanently, with no way back.

### Lessons

| | |
| --- | --- |
| Stash beats discard when unsure | It costs one extra command and is fully reversible |
| Git handles most renames itself | The document needed no manual work at all |
| Check sizes before discarding | `wc -c` vs `git show HEAD:<file> \| wc -c` |
| Verify before `stash drop` | It is the last copy once a pop has conflicted |
| Renames are disruptive in a shared repo | Agree on folder names early, rename rarely |

---

## 10. Undoing Things

Ordered from safe to dangerous.

| Goal | Command | Recoverable? |
| ---- | ------- | ------------ |
| Unstage a file, keep edits | `git restore --staged <file>` | Yes |
| See what changed | `git diff` / `git diff --staged` | Read-only |
| Cancel a merge in progress | `git merge --abort` | Yes |
| Undo the last commit, keep changes | `git reset --soft HEAD~1` | Yes |
| Undo the last commit, unstage | `git reset HEAD~1` | Yes |
| Reverse a **pushed** commit | `git revert <hash>` | Yes — makes a new commit |
| **Discard uncommitted edits** | `git checkout -- <file>` | **NO** |
| **Throw away commits and edits** | `git reset --hard <hash>` | **Commits yes, edits no** |

### The distinction that matters

**Committed work is almost always recoverable** — `git reflog` remembers where
every branch has pointed for about 90 days, even after a `reset --hard`.

**Uncommitted work is not.** Git has never seen it. `git checkout --` and
`git reset --hard` erase it with no trace.

> **Commit early. A commit is a save point, and save points are what make
> mistakes cheap.**

On a shared branch use `git revert`, not `git reset`. Revert adds a new commit
that undoes the old one; reset rewrites history and forces everyone else to
untangle it.

---

## 11. Rules of Thumb

1. **`git pull` before you start.** Every session. Not negotiable.
2. **Commit before you pull.** A clean tree means a merge can never be blocked.
3. **Push as soon as something works.** Unpushed commits are invisible to your
   collaborator and grow into conflicts.
4. **Never `git checkout --` without checking what you would lose first.**
5. **Prefer `git stash` over discarding** when you are not sure.
6. **Never `git push --force`** on `main`.
7. **Read `git status` before every commit.** It is three seconds and it catches
   binaries, stray files, and unresolved conflicts.
8. **Stay in your own folder.** `Malikh_Code/` and `Aafren_Code/` do not collide.
   Shared files at the repo root do.
9. **Do not commit build output.** `build/`, `*.o`, `*.dSYM/` — see
   [build_and_makefile.md](build_and_makefile.md).
10. **Agree on folder names once.** Renames force a conflict on everyone who has
    uncommitted work.

### Housekeeping: identity

This repo's history contains four author identities for two people:

```
5  Abdulmalikhtk          3  abdulmalikhtk
5  Aafren                 3  Aafren Fathima M
```

Harmless, but it makes `git log --author` and contribution stats unreliable. Set
it once per clone:

```bash
git config user.name  "Abdulmalikhtk"
git config user.email "abdulmalikhtk@gmail.com"
git config user.name        # verify
```

---

## 12. Quick Reference

```bash
# Daily
git pull                            # ALWAYS first
git add .
git status                          # read before committing
git commit -m "message"
git push

# Where am I
git status
git status --short                  # two-letter codes
git status --untracked-files=all    # see inside new folders
git log --oneline -10
git log --oneline -5 origin/main    # what the remote has
git branch -vv                      # ahead/behind count

# Pull refused: local changes
git stash                           # park
git pull
git stash pop                       # restore
git stash list                      # what is parked
git stash show -p                   # inspect before restoring
git stash drop                      # delete — only after verifying

# Conflicts
git status                          # which files
git diff                            # what conflicts
git add <file>                      # mark one resolved
git commit                          # finish the merge
git merge --abort                   # cancel the whole thing

# Modify/delete (usually a rename)
cp old/path new/path
git rm old/path
git add new/path

# Undo
git restore --staged <file>         # unstage, keep edits
git reset --soft HEAD~1             # undo last commit, keep everything
git revert <hash>                   # reverse a pushed commit
git checkout -- <file>              # DISCARD edits — permanent
git reflog                          # find lost commits

# Before discarding, check what you would lose
git diff <file>
wc -c <file>
git show HEAD:<file> | wc -c
```

### If you are stuck

```bash
git status
```

Read it properly. Git states the problem and usually prints the exact command to
fix it. Almost every situation in this document was diagnosable from `git status`
alone.
