# -*- coding: utf-8 -*-
"""
Created on Mon Mar 11 08:28:33 2024

@author: Acer
"""

def validate(account_number, valid_accounts):
    for i in valid_accounts:
        if (i == account_number):
            print("The charge account number", account_number, "is valid.")
            return
    print("The charge account number", account_number, "is invalid.")
           
        
def main():
    valid_accounts = [5448215, 5454386, 6548941, 5465489, 3134893, 8793468,
                    8348921, 2363486, 4983769, 6431923, 1497986, 2613583,
                    5658845, 4520125, 7895122, 8777541, 8451277, 1302850,
                    8080152, 4562555, 5552012, 5050552, 7825877, 1250255,
                    1005231, 6545231, 3852085, 7576651, 7881200, 4581002]

    user_input = int(input("Enter your charge account number: "))
    
    validate(user_input, valid_accounts)

    
main()