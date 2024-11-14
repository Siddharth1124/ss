#!/bin/bash 

adbook='MyAdressBook.txt';

createAdressbook(){
	if [ ! -f $adbook ]; then 
		echo -e "name\tphone\temail" > $adbook
		echo "Adressbook created successfully"
	else 
		echo "Adressbook already exists"
	fi
}

viewAdressbook(){
	echo -e '\n'
	cat $adbook
	echo -e '\n'
}

insertData(){
	echo "Enter name"
	read name
	echo "Enter mobile no"
	read mno
	echo "Enter email"
	read email

	echo -e "$name\t$mno\t$email" >> $adbook
}

deleteData(){
	echo "Enter name of data to be deleted"
	read name

	if [ -f $adbook ]; then
		grep -v "^$name" $adbook > temp.txt && mv temp.txt $adbook
		echo "Record deleted successfully"
	else 
		echo "No address book is selected"
	fi
}

modifyData(){
	echo "Enter name of the record to be modified"
	read name

	if grep -q "^$name" $adbook; then
		grep -v "^$name" $adbook > temp.txt
		mv temp.txt $adbook

		echo "Enter new name"
		read new_name
		echo "Enter new mobile no"
		read new_mno
		echo "Enter new email"
		read new_email

		echo -e "$new_name\t$new_mno\t$new_email" >> $adbook
		echo "Record modified successfully"
	else
		echo "Record not found"
	fi
}

a=1
while [ $a -eq 1 ]; do 
	echo "Enter your choice"
	echo "-----------------------------------"
	echo -e "1.Create Address Book \n2.View Address Book \n3.Insert a record \n4.Delete a record \n5.Modify a record \n6.Exit"
	echo "-----------------------------------"
	read choice
	
	case $choice in 
		1)
			createAdressbook 
			;;
		2)
			viewAdressbook
			;;
		3)
			insertData
			;;
		4)
			deleteData
			;;
		5)
			modifyData
			;;
		6)
			a=0
			;;
		*)
			echo "Invalid choice"
			;;
	esac
done
