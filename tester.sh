#!/bin/bash

#!/bin/bash

while read b; do
	echo "Testing $b"
    eval valgrind "$b"
    a=$?  # Capture the exit status
    if [ "$a" -eq 1 ]; then
        echo -e "\033[32m✅\033[0m"  # Print green checkmark
    else
        echo "❌"
    fi
done < tests
