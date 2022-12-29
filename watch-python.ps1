#pkg install watchexec
#cargo install watchexec-cli
# --force-poll: Termux doesn't seem to support inotify
watchexec --force-poll 1000 -c -r -e py "python main.py"
