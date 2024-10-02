#!/bin/bash

# Read parent pid, child pid
while [ "$#" -gt 0 ]; do
  case "$1" in
    --parent)
      parent="$2"
      shift 2
      ;;
    --child)
      child="$2"
      shift 2
      ;;
    --path)
      path="$1"
      shift 1
      ;;
    *)
      echo "Unknown parameter passed: $1"
      exit 1
      ;;
  esac
done

# Check if parent or child is empty
if [ -z "$parent" ] || [ -z "$child" ]; then
  echo "Usage: $0 --parent PARENT_PID --child CHILD_PID [--path]"
  exit 1
fi

########
# TODO #
########
tmp=$child
data=()
idx=0
data[idx]=$child
idx=$((idx+1))
group=$(ps -o pgid= -p $child)
#echo $group
while [ $tmp -ne $parent ]; do
	tmp=$(ps -o ppid= -p $tmp)
	#echo "tmp:$tmp"
	if [[ $tmp -lt $group ]]; then
		echo No
		exit 1
	else 
		data[idx]=$tmp
		idx=$((idx+1))
	fi
done
idx=$((idx-1))
echo Yes
if [ -n "$path" ]; then
	while [ $idx -gt -1 ]; do
		echo -n ${data[idx]}
		if [ $idx -gt 0 ]; then
			echo -n " -> "
		fi
		idx=$((idx-1))
	done
fi


# The code below is only for demonstration purposes, please remove it before submitting.
# echo "parent pid: $parent, child pid: $child"
