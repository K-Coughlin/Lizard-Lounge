from flask import Flask, render_template, jsonify, request

app = Flask(__name__)

devices = {
    "fan":"off",
    "pump":"off",
    "relay1":"off",
    "relay2":"off",
    "relay3":"off"
}

temps = {
    "temp1":0.0,
    "hum1": 0.0,
    "temp2":0.0,
    "hum2":0.0,
}

sensors = {
    "UV":0.0,
    "water":0
}

thresholds = {
    "hot_temp":-1.0,
    "low_temp":-1.0,
    "hi_humid":-1.0,
    "lo_humid":-1.0
}

feedback = "off"

@app.route('/')
def index():
    return render_template('index.html')

# Single endpoint for updating temperature and humidity data
@app.route('/update_temps', methods=['POST'])
def update_temps():

    data = request.json  # Get the JSON payload

    # Update the global variables if the keys exist in the payload
    if 'temp1' in data:
        temps["temp1"] = round(float(data['temp1']), 2)
    if 'hum1' in data:
        temps["hum1"] = round(float(data['hum1']),2)
    if 'temp2' in data:
        temps["temp2"] = round(float(data['temp2']),2)
    if 'hum2' in data:
        temps["hum2"] = float(data['hum2'])

    # Return a success response
    return jsonify(success=True)

@app.route('/toggle_feedback')
def toggle_feedback():
    global feedback  # Access the global feedback variable
    new_state = request.args.get('state')

    if new_state in ['on', 'off']:
        feedback = new_state
        print(f"Feedback state updated to: {feedback}")
        return jsonify({"feedback": feedback})
    else:
        return jsonify({"error": "Invalid state"}), 400


@app.route('/update_sensors', methods=['POST'])
def update_sensors():

    data = request.json  # Get the JSON payload

    if 'UV' in data:
        temps["UV"] = round(float(data['UV']),1)
    if 'water' in data:
        temps["water"] = int(data['water'])

    # Return a success response
    return jsonify(success=True)

@app.route('/toggle_device')
def toggle_device():
    device = request.args.get('device')
    new_state = request.args.get('state')
    
    if device in devices:
        devices[device] = new_state
        print(f"{device} state updated to: {new_state}")
        return jsonify({device: new_state})
    else:
        return jsonify({"error":"Device not found"}), 404

@app.route('/update_thresholds', methods=['POST'])
def update_thresholds():
    data = request.json  # Get the JSON payload

    # Update the global thresholds if the keys exist in the payload
    if 'hot_temp' in data:
        thresholds["hot_temp"] = float(data['hot_temp'])
    if 'low_temp' in data:
        thresholds["low_temp"] = float(data['low_temp'])
    if 'hi_humid' in data:
        thresholds["hi_humid"] = float(data['hi_humid'])
    if 'lo_humid' in data:
        thresholds["lo_humid"] = float(data['lo_humid'])

    # Return a success response
    return jsonify(success=True)

@app.route('/data')
def data():
    combined_data = {
        "devices":devices,
        "temps":temps,
        "thresholds":thresholds,
        "feedback":feedback
        }
    return jsonify(combined_data)

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0')