# Clear the terminal screen for a clean output
clear

# Initialize the choice variable 'c' to 0
c=0

# While loop keeps running the menu until the user chooses to exit (option 7)
#The test command checks whether the condition is true, i.e., whether c is not 7.
#This is a basic command used for evaluating conditions. It returns true (0) if the condition is true and false (non-zero) if it is false.
while test $c != 7
do
    # Display the menu to the user with options for creating, viewing, inserting, etc.
    echo "----------------------------"
    echo "1-> Create  2-> View  3-> Insert  4-> Delete  5-> Modify  6-> Search  7-> Exit"
    echo "----------------------------"
    
    # Prompt the user for a menu choice
    #The read command reads input from the user. The -p flag This flag is used with read to specify a prompt message. 
    #Without -p, read just waits for input without printing any message.
    #c: This is the variable where the user's input (menu choice) is stored.
    read -p "Enter your choice: " c
    echo "----------------------------"
    
    # 'case' statement for handling the different menu options based on the user's input
    #used to evaluate the value of c and execute the corresponding block of code.
    case "$c" in
    ("1") 
        # Option 1: Create Address Book
        echo "Create Address Book"
        echo "Enter the Filename: "
        read file
        # Create an empty file with the entered name
        touch "$file"
        echo "File created successfully."
        echo "----------------------------"
        ;;
    
    ("2")
        # Option 2: View Address Book
        echo "View Address Book"
        # Check if the file exists before trying to display it
        if [ -f "$file" ]; then   #The -f flag is used to check if the file exists and is a regular file (not a directory).
            # Display the content of the file
            cat "$file" #The cat command displays the content of a file. Here, it prints the contents of the file specified by the file variable.
        else
            echo "No file to display. Please create a file first."
        fi
        echo "----------------------------"
        ;;
    
    ("3")
        # Option 3: Insert Records
        echo "Insert Records"
        it=0 # Initializes the counter it to zero. This will be used to keep track of how many records have been entered.
        # Prompt the user for the number of records to be added
        read -p "Enter the number of records: " n
        
        # Loop to insert multiple records as specified by the user
        while [ $it -lt $n ]
        do
            echo "Enter ID:"
            read id1
            echo "Enter Name:"
            read nm
            echo "Enter Address:"
            read add
            
            # Validate the address (should contain only alphanumeric characters)
            #!: Negates the condition, so the loop continues if the condition is false (invalid address).
            #=~: This operator is used to match a string against a regular expression.
            #(^ denotes the start of the string, [A-Za-z0-9] matches letters and numbers, and + means "one or more").
            while [[ ! "$add" =~ ^[A-Za-z0-9]+ ]]; do
                echo "Enter a valid address:"
                read add
            done
            
            echo "Enter Phone Number (10 digits):"
            read ph
            # Validate the phone number (must be 10 digits)
            while [[ ! $ph =~ ^[0-9]{10}$ ]]; do
                echo "Please enter a valid phone number:"
                read ph
            done
            
            echo "Enter Email:"
            read em
            # Validate the email format
            while [[ ! $em =~ ^[a-z0-9._%-+]+@[a-z]+\.[a-z]{2,4}$ ]]; do
                echo "Please enter a valid email address:"
                read em
            done
            
            # Append the new record to the address book file
            echo "$id1,$nm,$add,$ph,$em" >> "$file"
            it=$((it + 1))
            echo "$it record(s) entered."
            echo "----------------------------"
        done
        ;;
    
    ("4")
        # Option 4: Delete a Record
        echo "Delete a Record"
        # Ask the user for the file and ID of the record to delete
        read -p "Enter the filename in which you want to delete: " file
        
        if [ -f "$file" ]; then
            # Read the ID to be deleted and use sed to remove the matching record
            #This command uses sed (stream editor) to delete a record by ID. 
            #The -i flag makes the changes in place (modifies the file directly), and /$id/d deletes the line containing the specified ID.
            read -p "Enter the ID you want to delete: " id
            sed -i "/$id/d" "$file"
            echo "Record deleted successfully."
        else
            echo "File not found."
        fi
        echo "----------------------------"
        ;;
    
    ("5")
        # Option 5: Modify a Record
        echo "Modify a Record"
        read -p "Enter the filename in which you want to modify: " file
        
        if [ -f "$file" ]; then
            # Prompt the user for the word they want to modify and the replacement
            read -p "Enter the word you want to modify: " word
            read -p "Enter the new word: " new_word
            # Use sed to replace the word in the file
            #-i_bkp: Creates a backup of the file before editing.
            #The s command replaces occurrences of $word with $new_word. 
            #The g flag means "global," so all occurrences are replaced.
            sed -i_bkp -e "s/$word/$new_word/g" "$file"
            echo "Record modified successfully."
        else
            echo "File not found."
        fi
        echo "----------------------------"
        ;;
    
    ("6")
        # Option 6: Search for a Record
        echo "Search for a Record"
        read -p "Enter the filename in which you want to search: " file
        
        if [ -f "$file" ]; then
            # Read the ID to search for and use grep to search in the file
            read -p "Enter the ID you want to search for: " id
            if grep -q "$id" "$file"; then
                grep "$id" "$file"  #grep: Searches through files for a specific pattern.
            else
                echo "Record not found."
            fi
        else
            echo "File not found."
        fi
        echo "----------------------------"
        ;;
    
    ("7")
        # Option 7: Exit the application
        echo "Exiting the Address Book application."
        echo "----------------------------"
        exit 0 #The exit command terminates the script. The 0 indicates a successful termination.
        ;;
    
    (*)
        # Catch-all for invalid input
        echo "Invalid option. Please choose a valid option."
        echo "----------------------------"
        ;;
    esac #This marks the end of the case statement (it's "case" spelled backward).
done # Marks the end of the while loop.

# The 'chmod +x 1_addressbook.sh' command is used to make the script executable.
# After making it executable, you can run the script using './1_addressbook.sh'
