# Campus Navigator

CSI 3334 Spring 2026 group project — a C++ console app for navigating and
managing campus locations. Built around a graph, a custom hash table, and
a BST, all wired together through an integration hub.

---

## Quick start

```bash
git clone https://github.com/jody-spikes/CampusNavigator.git
cd CampusNavigator
make
make run
```

You should see a 10-option menu. Type `0` to quit. If that works, your
setup is good. If not, check the troubleshooting section below.

---

## Prerequisites

You need `g++` (with C++17 support) and `make` installed.

### macOS

```bash
xcode-select --install
```

This installs both `g++` (as clang, which is fine) and `make`.

### Linux (Ubuntu / Debian)

```bash
sudo apt update
sudo apt install build-essential git
```

### Windows

The Makefile-based workflow needs a Unix-style shell. Easiest option is
**MSYS2**:

1. Install from [msys2.org](https://www.msys2.org/).
2. Open the "MSYS2 UCRT64" terminal.
3. Run: `pacman -Syu` (update), then `pacman -S mingw-w64-ucrt-x86_64-gcc make git`.
4. Use that terminal (not regular Command Prompt / PowerShell) for all
   git and make commands.

Alternative: WSL (Windows Subsystem for Linux) — install Ubuntu through
`wsl --install` and follow the Linux instructions.

### Verify

```bash
g++ --version
make --version
git --version
```

All three should print version info.

---

## Editor: VS Code (recommended)

The repo includes `.vscode/tasks.json` and `.vscode/launch.json` so
everyone gets the same build and debug experience.

1. Install [VS Code](https://code.visualstudio.com/).
2. Install the **C/C++** extension by Microsoft.
3. Open the project folder: `code .` from inside `CampusNavigator/`.

Once open:

- **Cmd+Shift+B** (Mac) / **Ctrl+Shift+B** (Win/Linux) → runs `make`.
- **F5** → builds and launches the debugger. Set breakpoints by clicking
  to the left of line numbers.

On Linux, the debugger needs `gdb` instead of `lldb`. Change the
`"MIMode"` line in `.vscode/launch.json` from `"lldb"` to `"gdb"`
locally (don't commit this — it will break macOS).

---

## Build commands

From the project root:

```bash
make         # compile everything in src/, produce ./campus_nav
make run     # compile and run
make clean   # remove compiled object files and the binary
```

The Makefile auto-discovers every `.cpp` in `src/`, so adding a new
source file just requires creating it and re-running `make`.

---

## Git workflow

We're all pushing to the same repo. To avoid stepping on each other:

```bash
git pull               # before you start working, get latest changes
# ...do your work...
git add <files>        # or `git add .` to stage everything
git commit -m "Clear description of what you did"
git pull               # one more pull in case someone pushed while you worked
git push
```

If `git pull` reports a merge conflict, don't panic — open the conflicted
file, look for the `<<<<<<<` and `>>>>>>>` markers, pick which version
you want, delete the markers, `git add` the file, `git commit`, `git push`.
If you're stuck, ask on the group chat before force-pushing anything.

**Commit often.** Small, frequent commits are easier to review and roll
back than one giant commit at the end of the week.

---

## Project layout

```
CampusNavigator/
├── .vscode/                 Shared editor config
├── data/
│   ├── locations.txt        Sample dataset (pipe-delimited)
│   └── edges.txt
├── src/
│   ├── Location.h           Shared types (DO NOT CHANGE without team agreement)
│   ├── Location.cpp
│   ├── Graph.h              \
│   ├── Graph.cpp             | Student 1: Graph & Routes
│   ├── NameHashTable.h      \
│   ├── NameHashTable.cpp     | Student 2: Hash Table
│   ├── SortedIndex.h        \
│   ├── SortedIndex.cpp       | Student 3: Sorted Index (BST/AVL)
│   ├── FileIO.h             \
│   ├── FileIO.cpp            | Student 4: File I/O
│   ├── Campus.h             \
│   ├── Campus.cpp            | Student 5 (Jody): Integration Hub
│   └── main.cpp             /
├── tests/                   (test drivers go here later)
├── .gitignore
├── Makefile
└── README.md
```

---

## Architecture

The **Graph** owns all `Location` data. Every location has a unique
`LocationID` (an int). The **NameHashTable** and **SortedIndex** don't
duplicate Location data — they store only `LocationID`s that point back
into the Graph.

The **Campus** class is the integration hub. `main.cpp` talks only to
`Campus`, and `Campus` keeps the Graph, hash table, and tree in sync on
every mutation.

```
                     Location.h  (shared types)
                          |
        +-----------+-----+-----+-----------+
        |           |           |           |
      Graph   NameHashTable  SortedIndex  FileIO
        \           |           /
         \          |          /
          +---------+---------+
                    |
                 Campus  ← integration hub
                    |
                 main.cpp
```

**Golden rule for mutations:** `addLocation`, `removeLocation`,
`updateLocation` in `Campus` must write to the Graph, the hash table,
AND the tree. If one is skipped, the structures drift out of sync and
lookups return stale data.

---

## File ownership and TODOs

Each owner: look at the `OWNER:` comment at the top of your files.
TODOs inside each function tell you exactly what to build.

### Student 1 — Graph & Route Engine

Files: `Graph.h`, `Graph.cpp`

- Implement adjacency-list storage for locations and edges.
- `addLocation`, `removeLocation`, `updateLocation`, `getLocation`,
  `getAllIDs`.
- `addEdge`, `removeEdge`, `getNeighbors` (treat edges as undirected —
  add both directions).
- `bfsPath` using a queue: track visited nodes and parent pointers,
  reconstruct the path by walking parents backwards.
- **Extra credit**: `dijkstraPath` using a priority queue.

Tip: when "removing" a location, mark it inactive instead of erasing
the slot. Shifting indices would invalidate every LocationID stored in
the other modules.

### Student 2 — Hash Table & Lookup

Files: `NameHashTable.h`, `NameHashTable.cpp`

- Separate chaining with a **custom linked list** (this satisfies the
  linked-list requirement for the whole project — make sure to mention
  it in the report).
- `insert`, `remove`, `find`, `clear`, `size`.
- `hash` — any reasonable string hash is fine.
- `rehash` — double the bucket count and redistribute entries when
  load factor exceeds ~0.75.

Tip: test by inserting 20+ entries to force at least one rehash and
confirm nothing breaks.

### Student 3 — Sorted Index

Files: `SortedIndex.h`, `SortedIndex.cpp`

- BST keyed by location name, storing LocationIDs.
- `insert`, `remove`, `inOrder` (in-order traversal for alphabetical output).
- AVL upgrade is worth points in the report if you have time.
- **Extra credit**: `findByPrefix` for autocomplete-style search.

Tip: remove is the hardest operation (three cases: leaf, one child, two
children). Use in-order successor for the two-child case.

### Student 4 — File I/O

Files: `FileIO.h`, `FileIO.cpp`

- `loadCampus`: read `locations.txt` and `edges.txt`, populate the
  Graph, hash table, and tree together.
- `saveCampus`: write current Graph state back to both files.
- A `split()` helper is already provided.

File format (pipe-delimited, see `data/locations.txt` and `data/edges.txt`):

```
# locations.txt
id|name|category|description
0|Thompson Hall|Academic|Main CS building

# edges.txt (treat as UNDIRECTED)
from_id|to_id|distance
0|1|150.5
```

Tip: when saving edges, only write each undirected edge once — e.g.
only write `(a, b)` when `a < b`.

### Student 5 — Integration & UI (Jody)

Files: `Campus.h`, `Campus.cpp`, `main.cpp`

- Wire the menu to `Campus` methods.
- Implement each mutation's 3-step mirror pattern (see the worked
  example in `Campus::addLocation`).
- Test the whole system end-to-end as other modules come online.

---

## Menu options (from the project spec)

```
1. Display all locations
2. Search for a location by name
3. Display locations by category
4. Find route between two locations
5. Add a location
6. Remove a location
7. Add a connection
8. Remove a connection
9. Update a location
0. Quit
```

---

## Troubleshooting

**"make: command not found"** — you don't have Make installed. See the
prerequisites section for your OS.

**"g++: command not found"** — same, install the toolchain.

**"undefined reference to ..." when linking** — you probably added a new
`.cpp` file in an editor other than VS Code and the Makefile didn't
pick it up. Run `make clean && make`.

**"Permission denied: ./campus_nav"** — run `chmod +x campus_nav`, or
just `make run` (which invokes the binary through make).

**Debugger won't launch on Linux** — change `"MIMode": "lldb"` to
`"gdb"` in `.vscode/launch.json` locally (don't commit the change).

**Can't push to GitHub ("authentication failed")** — GitHub doesn't
accept passwords for git. Either set up a Personal Access Token or
use SSH keys. Ask Jody for help if you get stuck.

**Merge conflict on `git pull`** — don't force-push. Open the
conflicted file, resolve the `<<<<<<<` / `>>>>>>>` sections, `git add`,
`git commit`, `git push`. Ask on the group chat if unclear.

---

## Team

| Student   | Role              | Files                                   |
|-----------|-------------------|-----------------------------------------|
| TBD       | Graph & Routes    | `Graph.h`, `Graph.cpp`                  |
| TBD       | Hash Table        | `NameHashTable.h`, `NameHashTable.cpp`  |
| TBD       | Sorted Index      | `SortedIndex.h`, `SortedIndex.cpp`      |
| TBD       | File I/O          | `FileIO.h`, `FileIO.cpp`                |
| Jody      | Integration & UI  | `Campus.h`, `Campus.cpp`, `main.cpp`    |

`Location.h` is shared. Don't change it without team agreement.
