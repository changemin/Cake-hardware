import firebase_admin, time, random
from firebase_admin import credentials
from firebase_admin import db
import time

# Fetch the service account key JSON file contents
cred = credentials.Certificate('icicle-cake-firebase-adminsdk-v6ri4-6b8acd52e9.json')
# Initialize the app with a service account, granting admin privileges
firebase_admin.initialize_app(cred, {
    'databaseURL': 'https://icicle-cake.firebaseio.com/'
})
while(True):
    ref = db.reference('/')
    ref.set({ 
        'rooms':{
            '1101':bool(random.getrandbits(1))
        },
        'users':{
            
        }
    })
    time.sleep(5)