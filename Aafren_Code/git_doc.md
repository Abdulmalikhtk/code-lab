# Collaborator Guide

How to work on `code-lab`. Read this once, then keep the cheat sheet at the bottom.

```
Repo      github.com/Abdulmalikhtk/code-lab
Branch    main
Owner     Abdulmalikhtk
```

---

## Contents

1. [Before You Start](#1-before-you-start)
2. [One-Time Setup](#2-one-time-setup)
3. [The Work Loop](#3-the-work-loop)
4. [Opening a Pull Request](#4-opening-a-pull-request)
5. [Staying in Sync](#5-staying-in-sync)
6. [Rules](#6-rules)
7. [Common Errors](#7-common-errors)
8. [Cheat Sheet](#8-cheat-sheet)

---

## 1. Before You Start

You need a GitHub account and an invite to the repo. The owner sends it from
Settings -> Collaborators. Accept the emailed invite before anything below will work.

Check git is installed:

```bash
git --version
```

---

## 2. One-Time Setup

### Get the code

```bash
git clone https://github.com/Abdulmalikhtk/code-lab.git
cd code-lab
```

You now have the whole repo and its full history.

### Set your identity

Do this inside the repo so your commits are attributed to you:

```bash
git config user.name  "Your Name"
git config user.email "your@email.com"

git config user.email          # verify
```

### Authentication

GitHub does not accept your account password over HTTPS. The first time you push,
it will print a one-time code like `XXXX-XXXX` and open a browser.

```
1. Copy the code from your TERMINAL (not the browser)
2. Paste it into the GitHub page that opens
3. Click Continue, then Authorize
4. Go back to the terminal - the push finishes on its own
```

Do not press Ctrl-C while it waits. It is polling GitHub for your approval.

You only do this once. macOS Keychain remembers it afterwards.

---

## 3. The Work Loop

### Always start from an up-to-date main

```bash
git switch main
git pull
```

### Make a branch for your task

```bash
git switch -c fix/null-head-crash
```

Never work directly on `main`. Name it after what you are doing:

```
    feat/       new functionality     feat/add-stack-class
    fix/        bug fixes             fix/null-head-crash
    docs/       documentation         docs/update-readme
    refactor/   restructuring         refactor/split-headers
```

### Do the work, then save it

```bash
# ... edit files, compile, test ...

git status                     # see what changed
git diff                       # see exactly what you changed
git add .                      # stage everything
git commit -m "Fix crash when head is null"
```

Commit messages should complete the sentence *"This commit will..."*.
Small, frequent commits beat one big one.

### Push your branch

```bash
git push -u origin fix/null-head-crash
```

`-u` is only needed the first time you push a given branch. After that, `git push`.

---

## 4. Opening a Pull Request

After pushing, go to the repo on GitHub. A banner appears:

```
    Compare & pull request
```

Click it, then:

```
1. Give it a clear title
2. Describe what changed and why
3. Click Create pull request
```

Now wait for review. Two things to know:

**A PR tracks your branch, not a snapshot.** If you push more commits to the same
branch, the PR updates automatically. Do not open a second PR.

**If changes are requested**, just fix them on the same branch:

```bash
# ... make the requested changes ...
git add .
git commit -m "Address review comments"
git push
```

The PR picks them up. When the owner merges, you are done — delete the branch when
GitHub offers.

---

## 5. Staying in Sync

Other people are also pushing. Before starting anything new:

```bash
git switch main
git pull
```

If your branch has been open a while and `main` has moved on:

```bash
git switch your-branch
git pull --rebase origin main
```

That replays your work on top of the latest `main`, so your PR merges cleanly.

---

## 6. Rules

**1. Never commit directly to `main`.** Always branch, always PR.

**2. One branch per task.** If you cannot name it in a short phrase, it is two tasks.

**3. Pull before you branch.** Branching from a stale `main` causes conflicts later.

**4. Never commit build output.** No `.o` files, no compiled binaries, no `.dSYM/`
folders. Check `git status` before every `git add .`.

**5. Never force-push a shared branch.** `git push --force` destroys other people's
work. If you think you need it, ask first.

**6. Test before you push.** Make sure it compiles and runs.

**7. Stay in your folder** unless the change genuinely belongs elsewhere.

---

## 7. Common Errors

### Push rejected

```
 ! [rejected]  main -> main (fetch first)
```

Someone pushed before you. Fix:

```bash
git pull --rebase
git push
```

### Need to specify how to reconcile divergent branches

```bash
git pull --rebase
```

To stop being asked every time:

```bash
git config --global pull.rebase true
```

### Local changes would be overwritten

You have uncommitted edits blocking a branch switch. Pick one:

```bash
git commit -am "WIP"      # save them
git stash                 # park them, restore later with git stash pop
git restore <file>        # throw them away - IRREVERSIBLE
```

### Merge conflict

Git marks the file:

```
<<<<<<< HEAD
    their version
=======
    your version
>>>>>>> your-branch
```

Open it, delete the three marker lines, keep the code that should win, then:

```bash
git add <file>
git rebase --continue      # or: git commit
```

Bail out any time with `git rebase --abort`. Nothing is lost.

### Committed to main by mistake

Do not push. Ask the owner before doing anything.

---

## 8. Cheat Sheet

```bash
# Start a task
git switch main
git pull
git switch -c feat/my-thing

# Save work
git status
git diff
git add .
git commit -m "Clear description"
git push -u origin feat/my-thing

# After the first push on that branch
git push

# Check where you are
git status                       # what changed
git branch                       # which branch am I on
git log --oneline --graph        # history

# Undo
git restore --staged <file>      # unstage            safe
git restore <file>               # discard edits      IRREVERSIBLE
```

**The one rule that matters.** Once work is committed it is very hard to lose. It is
uncommitted work that is fragile. Commit early, commit often, and ask before doing
anything with `--force` in it.
