#!/bin/bash

# Author: Rushabh Goswami
# Description: This script takes a UID as input in argument and prints the person's username, home directory,
#              	default shell, group ID, group name, and other groups the person belongs to.
# Command to run this script: ./GID_firstname_groups.sh <uid>
# Input: A user ID (UID).
# Output: Username, Home Directory, Shell, Group ID, Group Name, and other groups the user belongs to.

# Check if the UID is provided as an argument
if [ -z "$1" ]; then
    echo "Error: UID is not provided."
    echo "Command: $0 <uid>"
    exit 1
fi

# Get user information from /etc/passwd using getent and awk
# 															If the condition ($3 == uid) is true, this block tells awk to store the specific fields in USER_INFO:
# 															$1: The username (e.g., rushabh4u)
# 																$6: The user's home directory (e.g., /home/rushabh4u)
# 																	$7: The user's default shell (e.g., /bin/bash)
# 																		$4: The group ID (GID) of the user (e.g., 1000)
USER_INFO=$(getent passwd | awk -F: -v uid="$1" '$3 == uid {print $1, $6, $7, $4}')

# Check if the user exists
if [ -z "$USER_INFO" ]; then
    echo "Error: User with UID $1 not found."
    exit 1
fi

# Extract username, home directory, shell, and group ID
# echo "$USER_INFO": Outputs the value stored in the USER_INFO variable.
# used pipe ' | ' to redirect the output of echo as a input to the cut command.
# cut command splits the output.
# -d' ' is used as a delimiter.
# -f1 is used to select the first field and so on.
USERNAME=$(echo "$USER_INFO" | cut -d' ' -f1)
HOMEDIR=$(echo "$USER_INFO" | cut -d' ' -f2)
SHELL=$(echo "$USER_INFO" | cut -d' ' -f3)
GID=$(echo "$USER_INFO" | cut -d' ' -f4)

# Get group name from /etc/group using the group ID (GID)
# getent command retrieves the entry from the /etc/group file that matches the group ID ($GID).
# The group file (/etc/group) has the format: groupname:x:groupID:groupmembers
# -d: is used as a delimiter.
# -f1 is used to select the first field and so on.
GROUP_NAME=$(getent group "$GID" | cut -d: -f1)

# Get other groups that the user belongs to
# groups command retrieves the list of groups that the specified user ($USERNAME) belongs to.
# -d: is used as a delimiter.
# -f2 is used to select the sencond field which is the usernames of the specific user.
USER_GROUPS=$(groups "$USERNAME" | cut -d: -f2)

# Display the extracted information
echo "Username: $USERNAME"
echo "Home Directory: $HOMEDIR"
echo "Shell: $SHELL"
echo "Group ID: $GID"
echo "Group Name: $GROUP_NAME"
echo "Other Groups: $USER_GROUPS"

exit 0





# input:
#	bash 164992_Rushabh_groups.sh 1000
#
# output:
#	Username: rushabh4u
#	Home Directory: /home/rushabh4u
#	Shell: /bin/bash
#	Group ID: 1000
#	Group Name: rushabh4u
#	Other Groups:  rushabh4u adm dialout cdrom floppy sudo audio dip video plugdev netdev

