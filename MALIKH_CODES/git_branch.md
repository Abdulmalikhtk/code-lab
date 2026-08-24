# Git — Branches

Companion to `git_doc.md`. That file covers the solo workflow on a single branch.
This one covers everything about branches.

```
Repo root   ~/coding_practise/CODE_PRACTICE
Remote      github.com/Abdulmalikhtk/code-lab
Branch      main
```

---

## Contents

1. [What a Branch Actually Is](#1-what-a-branch-actually-is)
2. [The Lifecycle](#2-the-lifecycle)
3. [The Rules](#3-the-rules)
4. [Naming](#4-naming)
5. [Create, List, Rename, Delete](#5-create-list-rename-delete)
6. [Switching With Uncommitted Changes](#6-switching-with-uncommitted-changes)
7. [Comparing Branches](#7-comparing-branches)
8. [Merge and Rebase](#8-merge-and-rebase)
9. [Merge Conflicts](#9-merge-conflicts)
10. [Tracking](#10-tracking)
11. [Recovering Things](#11-recovering-things)
12. [Common Errors](#12-common-errors)
13. [Cheat Sheet](#13-cheat-sheet)

---

## 1. What a Branch Actually Is

Not a copy of the files. A branch is a **movable pointer to a commit** — a small
text file in `.git/refs/heads/` containing a hash. Creating one is instant and
costs about 40 bytes.

Start state. Two pointers on one commit.

```
  e50f33e  <--  main
           <--  HEAD
```

After `git switch -c feat/reverse`. Still one commit, nothing copied.

```
  e50f33e  <--  main
           <--  feat/reverse  <--  HEAD
```

After two commits. Only the pointer I am on moves.

```
  e50f33e  <--  main
     |
     +--> 9c1f2a8 --> 4d7b3e1  <--  feat/reverse  <--  HEAD
```

`main` never moved. That is the whole value: the experiment cannot damage it.

---

## 2. The Lifecycle

### Start

```bash
git switch main                          # start from main
git pull                                 # make sure it is current
git switch -c feat/linked-list-reverse   # create and move
```

### Work

```bash
git add .
git commit -m "Add reverse() to linked list"
git push -u origin feat/linked-list-reverse    # -u once per branch
```

### Finish

```bash
git switch main
git pull
git merge feat/linked-list-reverse
git push

git branch -d feat/linked-list-reverse               # delete local
git push origin --delete feat/linked-list-reverse    # delete remote
```

---

## 3. The Rules

**1. `main` always works.** Anyone should be able to clone `main` and have it
compile. Broken code lives on a branch until it is no longer broken.

**2. One branch per task.** Not per day, not per person. A branch is a unit of work
with a clear "done". If it cannot be named in a short phrase, it is two branches.

**3. Keep them short-lived.** Hours or days, not weeks. The longer a branch lives,
the further `main` drifts and the worse the eventual conflict.

**4. Always branch from an up-to-date `main`.** Run `git switch main && git pull`
first. Branching from stale `main` means merging someone else's old state back in.

**5. Descriptive names.** See section 4.

**6. Commit small and often.** A commit should be one logical change, with a message
that completes the sentence *"This commit will..."*. `git commit -m "stuff"` is a
note to nobody.

**7. Never force-push a branch someone else uses.** `git push --force` rewrites
history. On an unshared branch that is fine. On `main`, or a branch a colleague has
pulled, it destroys their work. Use `--force-with-lease` if it is unavoidable — it
refuses when the remote has commits I have not seen.

**8. Delete after merging.** Merged branches are clutter. The commits live on in
`main`; the pointer is disposable.

---

## 4. Naming

Lowercase, hyphens, a prefix that says what kind of change it is.

| Prefix      | Use for            | Example                    |
| ----------- | ------------------ | -------------------------- |
| `feat/`     | new functionality  | `feat/linked-list-reverse` |
| `fix/`      | bug fixes          | `fix/null-head-crash`      |
| `docs/`     | documentation      | `docs/git-notes`           |
| `refactor/` | restructuring      | `refactor/rule-of-five`    |

Never `test`, `temp`, `new`, or `abdul-branch`. In three weeks they mean nothing.

---

## 5. Create, List, Rename, Delete

### Create and switch

```bash
git switch -c feat/reverse         # create from current commit, move to it
git switch -c feat/reverse main    # create from main specifically
git switch feat/reverse            # move to an existing branch
git switch -                       # jump back to the previous branch
git switch main                    # back to main
```

`git switch -` toggles like `cd -`. Used constantly.

### List

```bash
git branch                 # local branches, * marks current
git branch -a              # local and remote
git branch -v              # with last commit on each
git branch --merged        # already merged into current, safe to delete
git branch --no-merged     # not merged, deleting loses work
```

`git branch --merged` before a cleanup is how to delete without thinking hard.

### Rename

```bash
git branch -m new-name              # rename the branch I am on
git branch -m old-name new-name     # rename another one
```

Renaming locally does not rename it on GitHub. If it is already pushed, push the new
name and delete the old.

```bash
git push -u origin new-name
git push origin --delete old-name
```

### Delete

```bash
git branch -d feat/reverse              # safe: refuses if unmerged
git branch -D feat/reverse              # force: deletes regardless
git push origin --delete feat/reverse   # delete the remote copy too
```

**`-d` vs `-D` is the pair to respect.** Lowercase checks first. Uppercase does not
ask. Use `-D` only to genuinely throw work away.

Deleting a branch never deletes commits — it removes a pointer. But commits with
nothing pointing at them become unreachable and are garbage-collected eventually.

---

## 6. Switching With Uncommitted Changes

Git blocks a switch that would overwrite edits.

```
error: Your local changes to the following files would be overwritten by checkout:
        linked_list.cpp
Please commit your changes or stash them before you switch branches.
```

This is git protecting me. Three ways out.

### Option 1: commit

The usual answer. A messy work-in-progress commit is fine and can be tidied later.

```bash
git commit -am "WIP: half-done reverse()"
```

### Option 2: stash

Park the changes on a shelf.

```bash
git stash              # save edits, clean the working tree
git switch main
# ... do the other thing ...
git switch feat/reverse
git stash pop          # bring the edits back and drop the stash
```

More stash:

```bash
git stash list         # what is on the shelf
git stash -u           # include untracked files (easy to forget)
git stash apply        # restore but KEEP it in the list
git stash drop         # discard the top entry
```

Stash is a stack and easy to forget about. Use it to cross the street, not as storage.

### Option 3: discard

If the edits are junk: `git restore file.cpp`. Irreversible.

**Note.** Git allows the switch when the edits do not conflict with the target
branch, and carries them across. Convenient, and occasionally confusing.

---

## 7. Comparing Branches

```bash
git diff main feat/reverse           # full difference
git diff main..feat/reverse --stat   # summary
git log main..feat/reverse           # commits feat/reverse has that main lacks
git log feat/reverse..main           # the reverse, what I am missing
git log --oneline --graph --all      # the whole shape, drawn
```

That last one is the most useful command for understanding repo state. Run it
whenever lost.

---

## 8. Merge and Rebase

### Fast-forward merge

`main` has not moved since branching, so git slides the pointer forward. No merge
commit.

```
  before:   A --- B  <- main
                   \
                    C --- D  <- feat/x

  after:    A --- B --- C --- D  <- main, feat/x
```

### Three-way merge

Both branches advanced. Git builds a merge commit with two parents.

```
  before:   A --- B --- E  <- main
                   \
                    C --- D  <- feat/x

  after:    A --- B --- E --- M  <- main
                   \         /
                    C ----- D
```

### Controlling it

```bash
git merge feat/x              # fast-forward when possible
git merge --no-ff feat/x      # always make a merge commit
git merge --squash feat/x     # collapse the whole branch into ONE commit
```

`--no-ff` keeps a visible record that a branch existed. `--squash` is good for a
branch with fifteen "wip" commits that should not enter `main`'s history.

### Rebase

```bash
git merge main        # merge commit, preserves true history
git rebase main       # replays my commits on top of main, linear history
```

**Golden rule: never rebase anything already pushed.** Rebasing creates new commits
with new hashes. If someone pulled the old ones, the histories diverge and fixing it
is genuinely painful.

Safe use: rebase a local, unpushed branch to tidy it before sharing. Otherwise merge.

---

## 9. Merge Conflicts

Git stops and marks the file.

```
<<<<<<< HEAD
    int size = count();          // what is on main
=======
    int size = length();         // what is on my branch
>>>>>>> feat/rename-size
```

Resolve in three steps.

```bash
# 1. Open the file. Delete the three marker lines, keep the code I want
#    (possibly a blend of both sides).

git add file.cpp     # 2. this is how I tell git "resolved"
git commit           # 3. finishes the merge
```

Bail out at any point with `git merge --abort`. Nothing is lost; back to before.

---

## 10. Tracking

A local branch can be linked to a remote one. That is what `-u` sets up.

```bash
git push -u origin feat/reverse    # create remote branch and link
git branch -vv                     # show every branch's upstream
```

Once linked, `git push`, `git pull`, and the ahead-behind line in `git status` all
work with no arguments — the same mechanism as `main` and `origin/main`.

Someone else's branch is easier still.

```bash
git fetch
git switch feat/their-work         # git auto-creates a local tracking branch
```

---

## 11. Recovering Things

### Deleted a branch by mistake

```bash
git reflog                         # every position HEAD has held
git branch feat/reverse a3f9c21    # recreate it at the found hash
```

The reflog keeps about 90 days. This is why committed work is nearly impossible to
lose — even "deleted" commits stay reachable until garbage collection.

### Detached HEAD

Ran `git checkout <hash>` and got `You are in 'detached HEAD' state`. I am on a
commit, not a branch. Looking around is fine. Committing here creates commits that
belong to no branch and will be collected.

```bash
git switch -c rescue-branch    # keep the work by naming it
git switch -                   # or leave without keeping anything
```

### Committed to the wrong branch

```bash
git switch correct-branch
git cherry-pick a3f9c21        # copy that commit here
git switch wrong-branch
git reset --hard HEAD~1        # remove it from the wrong branch
```

`reset --hard` destroys uncommitted work. Check `git status` is clean first.

---

## 12. Common Errors

| Message                                   | Means                            | Fix                                          |
| ----------------------------------------- | -------------------------------- | -------------------------------------------- |
| `local changes would be overwritten`      | uncommitted edits block a switch | commit, stash, or restore                     |
| `branch 'x' is not fully merged`          | `-d` refusing to lose work       | merge it, or `-D` to force                    |
| `src refspec main does not match any`     | pushing a branch with no commits | commit first                                  |
| `no upstream branch`                      | never pushed this branch         | `git push -u origin <branch>`                 |
| `You are in 'detached HEAD' state`        | on a commit, not a branch        | `git switch -c name` to keep, `git switch -` to leave |

---

## 13. Cheat Sheet

```bash
# Create and move
git switch -c feat/x            # create and switch
git switch main                 # switch
git switch -                    # previous branch

# Inspect
git branch -v                   # list with last commit
git branch --merged             # safe to delete
git log --oneline --graph --all # the whole picture
git log main..feat/x            # what feat/x adds

# Park work
git stash -u                    # shelve, including untracked
git stash pop                   # unshelve

# Finish
git switch main
git pull
git merge feat/x
git push
git branch -d feat/x
git push origin --delete feat/x

# Rescue
git reflog                      # find any lost commit
git branch saved <hash>         # rescue it
```

**Reality check.** `code-lab` is currently solo, so none of this is load-bearing
yet. Branches are still worth using alone — for isolating an experiment that might
get thrown away, or working on two things without tangling them. If a branch has no
reason to exist, committing straight to `main` on a personal repo is fine and normal.
Learn the workflow now so it is automatic when it matters.
