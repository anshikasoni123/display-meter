# importing flask modules
from flask import Flask , request , render_template , jsonify

# importing firebase_admin module
import firebase_admin

# importing firestore.py module to create firestore client
from firebase_admin import firestore

# importing credentials.py module from firebase_admin folder
from firebase_admin import credentials

# creating authentication file
cred = credentials.Certificate("write the path for your key")

# connect this python script/app with firebase using the authentication credentials
firebase_admin.initialize_app(cred)

# creating firestore client
firebase_db = firestore.client()


# creating flask object
app = Flask(__name__)

@app.route("/add-data", methods=["POST"])
def add_data():
    try:
        temperature = request.json.get("temperature")
        document_ref = firebase_db.collection("data")
        add_values = document_ref.document().create(dict(temperature=temperature, date=datetime.datetime.utcnow()))
        return jsonify({
            "status": "success"
        }), 201
    except Exception as e:
        return jsonify({
            "status": "error",
            "message": str(e)
        }), 400

@app.route("/")
def index():
    try:
        document_ref = firebase_db.collection("data")
        data = document_ref.order_by("date", direction='DESCENDING').limit(1).get()[0].to_dict()
        return render_template("/home/home.html", data=data)
    except Exception as e:
    
        print(str(e))
        return jsonify({
            "status": "error",
            "message": "No data in database yet!"
        }), 400



# start the server
if __name__  ==  "__main__":
    app.run(host = '0.0.0.0' , debug = True)

