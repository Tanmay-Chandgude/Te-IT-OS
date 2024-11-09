clear

c=0

while test $c != 7
do
    echo "----------------------------"
    echo "1-> Create  2-> View  3-> Insert  4-> Delete  5-> Modify  6-> Search  7-> Exit"
    echo "----------------------------"
    
    read -p "Enter your choice: " c
    echo "----------------------------"
    
    case "$c" in
    ("1") 
        echo "Create Address Book"
        echo "Enter the Filename: "
        read file
        touch "$file"
        echo "File created successfully."
        echo "----------------------------"
        ;;
    
    ("2")
        echo "View Address Book"
        if [ -f "$file" ]; then
            cat "$file"
        else
            echo "No file to display. Please create a file first."
        fi
        echo "----------------------------"
        ;;
    
    ("3")
        echo "Insert Records"
        it=0
        read -p "Enter the number of records: " n
        
        while [ $it -lt $n ]
        do
            echo "Enter ID:"
            read id1
            echo "Enter Name:"
            read nm
            
            echo "Enter Address:"
            read add
            while [[ ! "$add" =~ ^[A-Za-z0-9]+ ]]; do
                echo "Enter a valid address:"
                read add
            done
            
            echo "Enter Phone Number (10 digits):"
            read ph
            while [[ ! $ph =~ ^[0-9]{10}$ ]]; do
                echo "Please enter a valid phone number:"
                read ph
            done
            
            echo "Enter Email:"
            read em
            while [[ ! $em =~ ^[a-z0-9._%-+]+@[a-z]+\.[a-z]{2,4}$ ]]; do
                echo "Please enter a valid email address:"
                read em
            done
            
            echo "$id1,$nm,$add,$ph,$em" >> "$file"
            it=$((it + 1))
            echo "$it record(s) entered."
            echo "----------------------------"
        done
        ;;
    
    ("4")
        echo "Delete a Record"
        read -p "Enter the filename in which you want to delete: " file
        
        if [ -f "$file" ]; then
            read -p "Enter the ID you want to delete: " id
            sed -i "/$id/d" "$file"
            echo "Record deleted successfully."
        else
            echo "File not found."
        fi
        echo "----------------------------"
        ;;
    
    ("5")
        echo "Modify a Record"
        read -p "Enter the filename in which you want to modify: " file
        
        if [ -f "$file" ]; then
            read -p "Enter the word you want to modify: " word
            read -p "Enter the new word: " new_word
            sed -i_bkp -e "s/$word/$new_word/g" "$file"
            echo "Record modified successfully."
        else
            echo "File not found."
        fi
        echo "----------------------------"
        ;;
    
    ("6")
        echo "Search for a Record"
        read -p "Enter the filename in which you want to search: " file
        
        if [ -f "$file" ]; then
            read -p "Enter the ID you want to search for: " id
            if grep -q "$id" "$file"; then
                grep "$id" "$file"
            else
                echo "Record not found."
            fi
        else
            echo "File not found."
        fi
        echo "----------------------------"
        ;;
    
    ("7")
        echo "Exiting the Address Book application."
        echo "----------------------------"
        exit 0
        ;;
    
    (*)
        echo "Invalid option. Please choose a valid option."
        echo "----------------------------"
        ;;
    esac
done





:'for output 

chmod +x 1_addressbook.sh

./1_addressbook.sh
'

