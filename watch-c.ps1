#pkg install watchexec
#cargo install watchexec-cli
# --force-poll: Termux doesn't seem to support inotify
# run build.ps1 when any c or h file changes
watchexec --force-poll 1000 -r -c -e c,h pwsh.exe build.ps1
