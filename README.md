# **Minishell**

Minishell is a simplified shell implementation designed for educational purposes. It aims to replicate some of the basic functionalities of a Unix shell, providing a hands-on way to learn about how shells operate.

## 📦 Installation

To install Minishell, clone the repository to your local machine and run the following command in the root of the project:

```bash
make all
```

This will compile the necessary files and create the minishell executable.

## ⚡ Usage

Once you have built Minishell, you can start it by executing the following command in your terminal:

```bash
./minishell
```

You are now ready to use Minishell! Try out commands as you would in any standard shell.

## 🌟 Features

Minishell supports several features to give you a taste of shell programming:

    Pipes: Chain commands together using pipes to direct the output of one command as the input to another. For example:

```bash
ls -la | grep mini
```

Multicommands: Execute multiple commands in sequence separated by semicolons. For example:

```bash
echo "hello" ; echo "world" ; echo "and other things"
```

Enjoy exploring Minishell and the world of shell programming!
