from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import time

crn = [21332,21341,21342,21334,21338,21374,20645]

url = 'https://kepler-beta.itu.edu.tr/ogrenci/DersKayitIslemleri/DersKayit'
driver = webdriver.Chrome()
driver.get(url)
user_id = driver.find_element(By.ID, "ContentPlaceHolder1_tbUserName")
user_id.send_keys("demirpence21")
password = driver.find_element(By.ID, "ContentPlaceHolder1_tbPassword")
password.send_keys("hSDkaya104502.&202")
button = driver.find_element(By.ID, "ContentPlaceHolder1_btnLogin")
button.click()
driver.get(url)

WebDriverWait(driver, 60).until(EC.presence_of_element_located((By.CLASS_NAME, "mb-4")))

parent = driver.find_element(By.CLASS_NAME, "mb-4")
crnList = parent.find_elements(By.CLASS_NAME, "form-control")
for i in range(len(crn)):
    crnList[i].send_keys(crn[i])
addButton = parent.find_element(By.TAG_NAME, "button")
addButton.click()

time.sleep(5)
    