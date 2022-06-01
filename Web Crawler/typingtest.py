# download latest driver: https://sites.google.com/chromium.org/driver/downloads
# references:
#   https://selenium-python.readthedocs.io/api.html
#   https://www.geeksforgeeks.org/web-driver-methods-in-selenium-python/

from selenium import webdriver
from selenium.webdriver.chrome.options import Options
import time

chrome_options = Options()
chrome_options.add_argument("--incognito")
chrome_options.add_argument("--window-size=1920x1080")
# chrome_options.add_argument('--no-sandbox')
# chrome_options.add_argument('--disable-dev-shm-usage')

# DRIVER_PATH = 'C:/WebDriver/bin/chromedriver.exe'
DRIVER_PATH = '/Users/carmenlee/Desktop/github/projects/Web Crawler/chromedriver' # update path if needed
url = 'https://10fastfingers.com/typing-test/english'

driver = webdriver.Chrome(options=chrome_options, executable_path=DRIVER_PATH)  # opens browser
# driver.close()
driver.get(url)     # accesses website
time.sleep(7)       # add delay to wait for website to fully load
active = True
while(active):
    timer = driver.find_element_by_id('timer').text     # finds the timer
    if timer == '0:00':
        active = False      # stops when timer reaches 0:00
    try:
        word = driver.find_element_by_class_name('highlight').text      # finds highlighted word
    except:
        active = False      # stops when no more words
    
    # print(timer, word)

    field = driver.find_element_by_id('inputfield')     # finds input field
    field.send_keys(word)       # sends the highlighted word followed by space
    field.send_keys(' ')

time.sleep(10)   # waits 10 secs before closing
driver.quit()
driver.close()

