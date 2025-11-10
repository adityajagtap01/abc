#!/ bin / bash

phonebook = "phonebook.txt"


    if[!-f "$phonebook"]; then
    touch "$phonebook"
fi

while true
do
    echo "-----------------------------------"
    echo "          PHONEBOOK MENU           "
    echo "1. Add new contact"
    echo "2. View all contacts"
    echo "3. Search by name or number"
    echo "4. Sort by last name"
    echo "5. Delete a contact"
    echo "6. Exit"
    echo "-----------------------------------"

    read -p "Enter your choice: " choice
    echo

    case $choice in
        1)
            read -p "Enter First Name: " fname
            read -p "Enter Last Name: " lname
            read -p "Enter Phone Number: " phone
            echo -e "$fname\t$lname\t$phone" >> "$phonebook"
            echo "Contact added successfully."
            ;;

        2)
            if [ ! -s "$phonebook" ]; then
                echo "Phonebook is empty."
            else
                echo "All contacts:"
                echo "-----------------------------------"
                cat "$phonebook"
                echo "-----------------------------------"
            fi
            ;;

        3)
            read -p "Enter name or phone number to search: " search
            grep -i "$search" "$phonebook" || echo "No match found."
            ;;

        4)
            sort -k2 "$phonebook" -o "$phonebook"
            echo "Phonebook sorted by last name."
            ;;

        5)
            read -p "Enter name or phone number to delete: " del
            grep -iv "$del" "$phonebook" > temp.txt && mv temp.txt "$phonebook"
            echo "Contact deleted successfully."
            ;;

        6)
            echo "Exiting program."
            exit 0
            ;;

        *)
            echo "Invalid choice. Try again."
            ;;
    esac

    echo
    read -p "Press Enter to continue..."
    clear
done      
