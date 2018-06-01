# Python Notebook Setup

* make sure python, pip, jupyter-notebook, and virtualenv are installed

```
pip --version
```

Note: pip3, python3 for those versions

* If not of the form below install,

```
sudo pacman -S jupyter-notebook
```

* to activate javascript widgets in notebooks run [the following](https://wiki.archlinux.org/index.php/Jupyter),

```
jupyter nbextension enable --py --sys-prefix widgetsnbextension
```

* setup a directory for the notebook `mkdir directory`

* start a tmux session

```
tmux list-sessions # to list current sessions
tmux new -s name-here # to create new session
tmux attach -t name-here # to attach to session
tmux kill-session -t name-here # to kill it
```

Note: `ctrl-b`, `d` to detach from session without closing

* initiate notebook,

```
virtualenv directory # to setup environment
source directory/bin/activate # to enter environment
deactivate # to exit
```
[Helpful Resource](http://docs.python-guide.org/en/latest/dev/virtualenvs/)

* install what you need with `pip` or `pip3`
