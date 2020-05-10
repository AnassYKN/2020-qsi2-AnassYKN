# Troll of Fame - ReasonML

This project uses [ReasonML] (https://reasonml.github.io) with the workflow [esy] (https://esy.sh/) and the build system [Dune] (https://github.com/ocaml / dune).

## Modules

ReasonML integrates a modular programming system. The modules offer an encapsulation mechanism and allow you to organize the code into logical units, by providing namespaces useful when using them. ReasonML offers a very powerful system of recursive and configurable modules which makes it possible to provide great genericity to the code.

In ReasonML, all the code is encapsulated in modules. If we put all the code from the first TP in a Game.re file, this automatically defines a Game module.

_The name of a module always starts with a capital letter, the convention is that we name the ReasonML files also starting with a capital letter but this is not an obligation: the file game.re would also have defined the module Game_

#### Open Modules


Imagine that we have the module and the sub-module

```reason
  module Fairy = {
    module Animal = {
      type t =
      | Unicorn
      | Dragon
      | Manticor
      | Mermaid;
    }

    let redDragon = Animal.Dragon;
  }
```

You will notice the naming of types `t`: this is a convention widely used in ReasonML / OCaml ecosystems, where the type named` t` indicates the main type inhabiting the module. We use `Animal.t` rather than` Animal.animal` although it is not an obligation.

To access the content of the module, it is possible to open it. Rather than writing:

```reason
  let defaultValue = Fairy.Animal.redDragon;
```

You can write, to access it in the whole of a file:

```reason
  open Fairy;
  let defaultValue = Animal.redDragon;
```

Or

```reason
  open Fairy.Animal;
  let defaultValue = redDragon;
```

The content of the module is visible in the scope. Above in the whole file but it is possible to have a scope by expression:

`` `reason
  let defaultValue = Fairy. (Animal.redDragon);
`` ''

or create a limited scrope:

`` `reason
  {
    open Fairy;
    let defaultValue = Animal.redDragon;
  }
`` ''

If you want to know more about the ReasonML rich module system, read [ResonML: modules] (https://oteku.github.io/reasonml-modules/)

## Getting started

- Install esy: `npm install -g esy`
- Install dependencies: `esy install`
- Build the app: `esy build`
- Run compiled executable: `esy x TOF.exe` _ (a sample troll of fame) _
- Run tests: `esy test`

Note: If you are using VSCode, you should install the module [OCaml and Reason IDE] (https://marketplace.visualstudio.com/items?itemName=freebroccolo.reasonml) and activate the lens parameter _Reason ›Codelens: Enabled_

```
troll-of-fame@0.0.0
│
├─test / lib /
│ name: Runner
│ hand: Runner
│ require: troll-of-fame
│
├─lib /
│ library name: Lib
│ namespace: troll-of-fame
│ require:
│
└─bin /
    name: TOF.exe
    main: TOF
    require: troll-of-fame
```
