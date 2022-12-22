#pkg install watchexec
#cargo install watchexec-cli
watchexec --force-poll 1000 -r -e py python main.py
