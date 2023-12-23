import mysql.connector     
import requests
import time
from bs4 import BeautifulSoup
"""
Created By: Tomasz Brauntsch
CS-288 007
Professor Ding
December 21, 2023
"""

countinstance = 0
try:
    while(True):
        URL = "https://finance.yahoo.com/most-active"
        r = requests.get(URL)
        if(r.status_code != 200):
            # URL = "https://finance.yahoo.com/most-active"
            r = requests.get(URL)
            if(r.status_code != 200):
                    exit(1) # Terminate
        cnx = mysql.connector.connect(user="lamp", password="lamp", database="cshwstock")
        cursor = cnx.cursor()
        add_stock_data = "INSERT INTO site_data (stock_symbol, stock_name, stock_price, stock_change, stock_volume) VALUES ("
 
        soup = BeautifulSoup(r.content, 'html.parser')
 
        mytrs = soup.body.tbody.find_all("tr")
        for tr in mytrs:
            mychildren = tr.findChildren()                                                                                   
            i = 0                                                                                                            
            for child in mychildren:                                                                                         
                if ((child.name == "td") and (i <= 5)):
                    if(i != 4 and i != 5):
                        add_stock_data += "\'" + child.text + "\', "
                        print(child.text)
                        # append to the string for stock data
                    if(i == 5):
                        print(child.text)
                        add_stock_data += "\'" + child.text + "\')"
                    i += 1
            cursor.execute(add_stock_data)
            cnx.commit()
            print(add_stock_data)
 
            add_stock_data = "INSERT INTO site_data (stock_symbol, stock_name, stock_price, stock_change, stock_volume) VALUES ("
            print()
            print()
 
        cursor.close()
        cnx.close()
        print("i: " + str(countinstance))
        time.sleep(20)
        # time.sleep(180)
        countinstance += 1
        # pump information to the mysql DB
except KeyboardInterrupt:
    exit(1)