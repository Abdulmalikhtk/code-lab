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
