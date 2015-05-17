# Import library
import imaplib

# Connect to Gmail
obj = imaplib.IMAP4_SSL('imap.gmail.com', '993')  

# Login to Gmail
obj.login('your_gmail_address','your_gmail_password')

# Print number of unread emails
print len(obj.search(None,'UnSeen')[1][0].split())