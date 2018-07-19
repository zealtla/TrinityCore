# Multitrainer [![Build Status](https://travis-ci.org/Rochet2/TrinityCore.svg?branch=multitrainer)](https://travis-ci.org/Rochet2/TrinityCore)

#### About
This patch was coded originally by Asandru.  
Multitrainer allows you to show multiple different trainer windows on an NPC.

Source: http://rochet2.github.io/Multitrainer.html

#### Installation

Available as:
- Direct merge: https://github.com/Rochet2/TrinityCore/tree/multitrainer
- Diff: https://github.com/Rochet2/TrinityCore/compare/TrinityCore:3.3.5...multitrainer.diff
- Diff in github view: https://github.com/Rochet2/TrinityCore/compare/TrinityCore:3.3.5...multitrainer

Using direct merge:
- open git bash to source location
- do `git remote add rochet2 https://github.com/Rochet2/TrinityCore.git`
- do `git pull rochet2 multitrainer`
- use cmake and compile

Using diff:
- DO NOT COPY THE DIFF DIRECTLY! It causes apply to fail.
- download the diff by __right clicking__ the link and select __Save link as__
- place the downloaded `multitrainer.diff` to the source root folder
- open git bash to source location
- do `git apply multitrainer.diff`
- use cmake and compile

#### Usage
The NPC is required to have `npcflag` set to `17`. The `trainer_type` can be `0`.  
In C++ you can pass the trainer entry to `SendTrainerList` function.  
In SQL in `world` database you can set the trainer entry to the `gossip_menu_option` table `ActionMenuID` column for an option that has `OptionType` set to `5`.

#### Bugs and Contact
Report issues and similar to https://rochet2.github.io/
