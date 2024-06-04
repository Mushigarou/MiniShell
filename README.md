# Mini Shell (As Beautiful as a Shell)

## Navigation

1. [Introduction](#introduction)
1. [Instalation and Usage](#instalation-and-usage)
    1. [Instalation](#instalation)
    1. [Usage](#usage)
1. [Parsing](#parsing)
    1. [Splitting](#splitting)
    1. [Identifying](#identifying)
1. [Author & Final mark](#author--final-mark)

## Introduction

The objective of this project is to implement a simple shell in **`C`**. This shell will handle various signals, special characters, and environment variables.

## Instalation and Usage

### Instalation

To install this project clone this project by running

```bash
    git clone 'git@github.com:jaguar-ks/MINI_SHELL.git'
```

cd to the project directory

```bash
    cd MINI_SHELL
```

make sure u have the ***`readline`*** library installed if you are on ***`macOS`*** you can run the following command to install it

```bash
    brew install readline
```

that assuming you already have brew if not you can know how to set it up [here](https://github.com/kube/42homebrew)

### Usage

After installing all depandencies you can run the following command on the root of the project:

```bash
    make && ./minishell
```

## Parsing

### Splitting

To parse the input prompt line, we first split the string by **spaces** outside of any quotes.

Subsequently, we iterate over the resulting list and further split any node that contains a redirection character, such as [**`<`**, **`>`**, **`>>`**, **`<<`**, **`|`**].

The process will result in a structure resembling the following:

![demonstration](./demo.png)

---

### Identifying

In this phase, we identify the pipe **`|`** and the redirections [**`<`**, **`>`**, **`>>`**, **`<<`**].

1. If we encounter one of [**`<`**, **`>`**, **`>>`**], it signifies that the subsequent node will be a **file**.
2. If we encounter **`<<`**, it indicates that the next node is a **delimiter** for the **heredoc**.
3. If we encounter **`|`**, it signifies that the next set of nodes, up to the next **`|`** or the end of the list, forms a separate command.

We then split the list at the **`|`** node if it exists; otherwise, we handle it as a single command.

> **Note:** If the first or the last node is **`|`**, or if we find a **`|`** immediately following a redirection [**`<`**, **`>`**, **`>>`**, **`<<`**], it results in a syntax error.

Next, we identify the **command** to be executed. This step is straightforward because we have already determined the positions of the **pipe** and the **redirections**.

1. To locate the **command**, we skip any node that has already been identified.
2. The first unidentified node encountered is deemed to hold our **command**.

Finally, we identify the flags and arguments.

1. After the command node, any unidentified node starting with `-` is considered a **flag**.
2. Any other unidentified node is considered an **argument**.

> **Note:** If a **flag** is found after an **argument**, it constitutes an error.

---

## Author & Final mark

This project was developed and validated by [`0xJ4GU4R`](https://github.com/jaguar-ks) and [`LeakedByteBuster`](https://github.com/LeakedByteBuster). With a final mark of:

![final_mark](./mark.png)
