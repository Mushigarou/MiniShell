# Mini Shell (As beautiful as a shell)

## Navigation
1. [Introduction](#introduction)
1. [Parsing](#parsing)

## Introduction

The project goal is to rewrite a simple shell in `C` handling some signals and some special characters and also enviremnet variables

## Parsing

To parse the prompt line first we split the string with **spaces** outside the quotes.

After that we iterate over the list and split every nodew that contain a redirection character [`<`, `>`, `>>`, `<<`, `|`].

after spliting every thing now we move to identify each node a what its position in the command line. If we find a pipe `|` that mean we have multiple commands.
