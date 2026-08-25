# Getting Started

Reading these notes, sharing the repo, and seeing what is actually in it.

```
Repo root   ~/coding_practise/CODE_PRACTICE
Remote      github.com/Abdulmalikhtk/code-lab
```

---

## Contents

1. [Viewing .md Files](#1-viewing-md-files)
2. [Letting Others Use the Repo](#2-letting-others-use-the-repo)
3. [Pull Requests](#3-pull-requests)
4. [Seeing the Folder Structure](#4-seeing-the-folder-structure)
5. [Adding a New Folder](#5-adding-a-new-folder)
6. [When Push Is Rejected](#6-when-push-is-rejected)

---

## 1. Viewing .md Files

Built into VS Code, no plugin needed.

| Shortcut           | Does                                      |
| ------------------ | ----------------------------------------- |
| `Cmd + K` then `V` | Preview side-by-side with the source      |
| `Cmd + Shift + V`  | Preview in a new tab                      |

`Cmd + K` then `V` is a chord: press `Cmd + K`, release both keys, then press `V`.

Side-by-side is the one to use. Source left, rendered right, scrolling in sync.

---

## 2. Letting Others Use the Repo

First thing that decides everything: **is the repo public or private?** The badge
next to the repo name on GitHub says which. Private means nobody can see it until
they are invited.

### Case A — they just want to use the code

Nothing needed from me if the repo is public.

```bash
git clone https://github.com/Abdulmalikhtk/code-lab.git
cd code-lab
```

They now have the full repo and its entire history. They can read it, build it and
experiment freely, but they **cannot push**. Their changes stay on their machine.

On a private repo this fails until they are added as a collaborator.

### Case B, Model 1 — Collaborator

For people I know. Grant direct push access:

```
GitHub repo -> Settings -> Collaborators -> Add people -> their username
```

They accept the emailed invite, then work exactly as I do:

```bash
git clone https://github.com/Abdulmalikhtk/code-lab.git
cd code-lab

git switch -c fix/null-head-crash        # never work directly on main
# ... edit, test ...
git add .
git commit -m "Fix crash when head is null"
git push -u origin fix/null-head-crash
```

**They can technically push straight to `main`.** To prevent that:

```
Settings -> Branches -> Add rule -> Require a pull request before merging
```

### Case B, Model 2 — Fork and pull request

For strangers and open source. No access granted. They click **Fork**, which copies
the repo to their own account.

```bash
git clone https://github.com/THEIR-NAME/code-lab.git
cd code-lab

git switch -c fix/null-head-crash
# ... edit, commit ...
git push -u origin fix/null-head-crash   # pushes to THEIR fork
```

Then they open a PR from their fork to my repo. They never touch my repository
directly. This is how all open source works, and it is the safe default for anyone
I do not know.

### Which model

| Situation                | Model        |
| ------------------------ | ------------ |
| Friend, colleague, team  | Collaborator |
| Stranger, open source    | Fork and PR  |

---

## 3. Pull Requests

A PR is a request to merge one branch into another, plus a place to discuss it.

Key property: **a PR tracks a branch, not a snapshot.** If they push three more
commits to the branch, the open PR updates automatically. Nobody reopens anything.

### As the owner

```
1. GitHub shows a banner: Compare & pull request
2. Open the PR, read the Files changed tab
3. Comment on specific lines, or approve
4. Merge pull request
5. Delete branch  (button appears right after merging)
```

### Testing their branch before merging

Reading a diff is not the same as running the code. Especially for C++.

```bash
git fetch origin
git switch fix/null-head-crash    # git creates a local branch tracking theirs
# ... compile it, run it, poke at it ...
git switch main                   # done looking
```

### After merging, sync locally

```bash
git switch main
git pull
```

My local `main` does not know about the merge until I pull. `origin/main` is a
cached pointer, not a live one.

---

## 4. Seeing the Folder Structure

### On github.com

The repo front page lists the root. Click a folder to descend, breadcrumbs to come
back. The icon at the top-left of the file list toggles a persistent sidebar tree.

Keyboard shortcuts, pressed while on the repo page:

| Key | Does                                            |
| --- | ----------------------------------------------- |
| `t` | File finder — fuzzy search every file in the repo |
| `.` | Opens github.dev, a full VS Code in the browser  |
| `?` | List all shortcuts                               |

`t` is the fast one. Start typing `git_br` and it jumps to `git_branch.md`.

### Locally — what is actually tracked

This is the important distinction. The folder contains files git does not track, and
those are **not** on GitHub.

```bash
git ls-files                                  # tracked = exactly what is on GitHub
git ls-files --others --exclude-standard      # untracked = NOT on GitHub
```

If something is missing from the website, it will show up in that second list.

### Plain folder tree

```bash
brew install tree
tree -I '.git'
```

Current state:

```
.
└── MALIKH_CODES
    ├── get_started.md
    ├── git_branch.md
    └── git_doc.md

2 directories, 3 files
```

Without installing anything:

```bash
find . -not -path "./.git/*" -not -name ".git"
```

**Note.** Only `git_doc.md` has been committed and pushed so far. `git_branch.md`
and `get_started.md` exist on disk but will not appear on GitHub until they are
committed. `git status` confirms which is which.

---

## 5. Adding a New Folder

```bash
cd ~/coding_practise/CODE_PRACTICE
mkdir aafren_codes
```

Or in VS Code: right-click empty space in the Explorer sidebar -> New Folder.

### Git ignores empty folders

**Git tracks files, not directories.** An empty folder is invisible to git:
`git status` will not mention it, `git add .` will not stage it, and it will never
appear on GitHub.

So put something in it:

```bash
touch aafren_codes/README.md      # a real file
touch aafren_codes/.gitkeep       # or a placeholder
```

`.gitkeep` is not a git feature. It is an agreed-on empty placeholder file. The
folder exists on GitHub because the file inside it does.

Then commit as usual:

```bash
git status                        # should now show ?? aafren_codes/
git add .
git commit -m "Add aafren_codes folder"
git push
```

### Naming consistency

`MALIKH_CODES` is uppercase and `aafren_codes` is lowercase. Git on macOS is
case-insensitive but case-preserving, while GitHub is case-sensitive. Mismatched
conventions cause real confusion later. Pick one style and keep it.

A case-only rename needs two steps, because a direct one is silently ignored:

```bash
git mv MALIKH_CODES malikh_codes_tmp
git mv malikh_codes_tmp malikh_codes
```

---

## 6. When Push Is Rejected

```
 ! [rejected]        main -> main (fetch first)
error: failed to push some refs
hint: Updates were rejected because the remote contains work that you do not
hint: have locally.
```

This means GitHub has a commit the laptop does not — usually from editing a file or
adding a README through the web interface.

```
  laptop:   A --- B --- C          my commits
              \
  GitHub:      A --- B --- W       W = the web commit I do not have
```

The histories diverged. Nothing is broken and nothing is lost.

### The fix

```bash
git pull --rebase
git push
```

### Why plain git pull is not enough

A bare `git pull` on divergent branches now stops with:

```
fatal: Need to specify how to reconcile divergent branches.
```

Git fetched the commit but will not guess how to combine it. The three options:

| Command                 | Result                                    |
| ----------------------- | ----------------------------------------- |
| `git pull --rebase`     | Replay my commits on top. Linear history. |
| `git pull --no-rebase`  | Create a merge commit. The old default.   |
| `git pull --ff-only`    | Only if I have no local commits. Refuses otherwise. |

`--rebase` is right here. Unpushed commits are safe to rebase — this is exactly the
case the golden rule permits.

```
  before:   e50f33e --- (my commit)             local main
                \
                 ------ b9c6d6d                 origin/main

  after:    e50f33e --- b9c6d6d --- (my commit) both
```

### Stop being asked every time

```bash
git config --global pull.rebase true
```

### If the rebase hits a conflict

Only happens when both sides touched the same lines.

```bash
# open the file, remove the <<<<<<< markers, keep what I want
git add <file>
git rebase --continue
```

Back out entirely with `git rebase --abort`. Nothing is lost.

### Confirm

```bash
git log --oneline --graph
```

The web commit should be in history with mine on top, and `main` and `origin/main`
back on the same commit.
