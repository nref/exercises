sudo apt -y install inotify-tools
while true; do 
  inotifywait -qm --event modify --format '%w' ./*.c | (./build.sh && ./run.sh)
done
