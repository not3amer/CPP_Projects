# Full_Bank_System
## note:
1- This system Built with C++ Lang, specifically in OOP style.  
2- This program uses text files (.txt) as databases, you can find those text files in "\bankSysInOOP\bankSysInOOP".  
3- To Run This Project you Should Download it and Open Project Folder With "Visual Studio" ,then Click on "bankSysInOOP.cpp" and Run it.  
4- the Default Username is "admin" and the Dafault Password is "admin".

## Now I will review the project through a picture and its explanation.
## Login Screen:
![2023-09-29_200850](https://github.com/not3amer/Full_Bank_System/assets/103201013/85691019-7411-405d-9d67-47ad99b1bacd)
Here system users can log in using their username and password, where the entered data is compared with the usernames and passwords (after decrypting the passwords in the “Users.txt” file)

- If any incorrect data is entered, an error message is given to the person trying to log in and the number of remaining attempts he has is shown. If we exceed the number of audible attempts (3), the system shuts down.
- If a correct user name and password are entered, the system will open and all the features offered by the system will be displayed, and the user can access them according to the permissions given to him - which will be discussed later -

Note: With each login, the user’s data, time and date of login to the system are recorded in a “LogRegister.txt” file.
______________________________________________________________________________________________________________________
## Main Menue Screen:
![2](https://github.com/not3amer/Full_Bank_System/assets/103201013/3f934007-a9ee-45ae-97f8-8cec17f3778f)
This screen shows the main menu of the program through which you can choose what you want to do. You can choose from 1 to 10. If you enter a choice that does not exist, an error message will appear and you will be given another opportunity to enter a correct choice.
Now let's start entering "Show Client List".
______________________________________________________________________________________________________________________
## Client List Screen:
![3](https://github.com/not3amer/Full_Bank_System/assets/103201013/394bc6a4-8903-44f9-8eb1-55b594d8684b)
This screen shows the number of customers registered with the bank and a detailed list of these customers’ data, such as account number, Pincode, name, phone number, email, and account Balance of the Client.  
This data is fetched from the file "Clients.txt".  
You Can Back From This Screen to Main Menue by Click Enter.  
______________________________________________________________________________________________________________________


