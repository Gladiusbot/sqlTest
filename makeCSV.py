import csv
import random
import time
import sys

it_companies = [
    "Apple", "Microsoft", "Amazon", "Google", "Facebook", "Alibaba", "Tencent",
    "Intel", "IBM", "Oracle", "Samsung", "NVIDIA", "Adobe", "Cisco", "HP",
    "Dell", "Sony", "Lenovo", "VMware", "Qualcomm", "Netflix", "Uber", "Spotify",
    "Salesforce", "Accenture", "Tesla", "Twitter", "LinkedIn", "HP Enterprise",
    "Hitachi", "Panasonic", "Hewlett Packard", "Siemens", "SAP", "Dell EMC",
    "Micron", "Nokia", "Yahoo", "Xerox", "Red Hat", "Infosys", "Cognizant",
    "Uber", "Lyft", "Airbnb", "Palantir", "Dropbox", "Snap", "Zynga", "Pinterest",
    "Slack", "Square", "Epic Games", "AMD", "Cisco", "Juniper Networks", "Qualtrics",
    "MongoDB", "ServiceNow", "Atlassian", "Twilio", "DocuSign", "Zoom Video",
    "Snowflake", "Splunk", "Fortinet", "Zscaler", "DocuWare", "CrowdStrike", 
    "Proofpoint", "FireEye", "Akamai", "F5 Networks", "Cloudflare", "Okta", "Box",
    "GitLab", "PagerDuty", "Elastic", "Cloudera", "DataRobot", "MongoDB", "Databricks",
    "Alteryx", "Anaplan", "Workday", "UiPath", "Blue Prism", "SAS", "Symantec",
    "Veritas", "Western Digital", "Micron", "Broadcom", "Cisco Meraki", "Eaton",
    "Honeywell", "Emerson", "ABB", "Rockwell Automation", "Schneider Electric",
    "National Instruments", "Texas Instruments", "Micron", "Marvell Technology",
    "Arrow Electronics", "TE Connectivity", "Flex", "Avnet", "Sony",
    "Samsung Electronics", "LG Electronics", "HTC", "ASUS", "Acer", "Foxconn",
    "Wipro", "HCL Technologies", "Tata Consultancy Services", "Infosys",
    "Tech Mahindra", "Cognizant", "Mindtree", "L&T Infotech", "Wipro",
    "Hexaware Technologies", "Mphasis", "Genpact", "Syntel", "iGate",
    "KPIT Technologies", "Zensar Technologies", "Persistent Systems", "Cyient",
    "NIIT Technologies", "Tata Elxsi", "Mindtree", "Hexaware Technologies",
    "Mphasis", "Genpact", "Syntel", "iGate", "KPIT Technologies", "Zensar Technologies",
    "Persistent Systems", "Cyient", "NIIT Technologies", "Tata Elxsi", "Mindtree",
    "Hexaware Technologies", "Mphasis", "Genpact", "Syntel", "iGate", "KPIT Technologies",
    "Zensar Technologies", "Persistent Systems", "Cyient", "NIIT Technologies", "Tata Elxsi"
]
header = ["NAME", "AMOUNT", "ACCOUNT_ID"]
csz = len(it_companies)
ITEMS_PER_FILE = 100000

def generateLine():
    idx = random.randint(0, csz - 1)
    res = []
    res.append(it_companies[idx])
    res.append(random.randint(1000, 100000))
    res.append(idx)
    return res

def writeCSV(filename):
    start_time = time.time()

    with open(filename, mode="w", newline="") as csv_file:
        csv_writer = csv.writer(csv_file)
        csv_writer.writerow(header)
        for i in range(ITEMS_PER_FILE):
            print(r"writing line:", i)
            bill_list = generateLine()
            csv_writer.writerow(bill_list)
    csv_file.close()

    end_time = time.time()
    elapsed_time = end_time - start_time
    print(f"运行耗时:{elapsed_time}秒")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("请输入文件名(.csv)作为参数, e.g. python makeCSV.py 1.csv")
        sys.exit(1)
    csv_file_path = sys.argv[1]
    writeCSV(csv_file_path)
