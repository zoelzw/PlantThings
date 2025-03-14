document.addEventListener("DOMContentLoaded", function () {
    const tempSpan = document.getElementById("temp");
    const humiditySpan = document.getElementById("humidity");
    const co2Span = document.getElementById("co2");

    function fetchSensorData() {
        fetch("/sensor")
            .then(response => response.json())
            .then(data => {
                tempSpan.textContent = data.temp;
                humiditySpan.textContent = data.humidity;
                co2Span.textContent = data.co2;
            })
            .catch(error => console.error("Error fetching sensor data:", error));
    }

    function sendLedData(led) {
        // let ledData = {};
        if (led === 'led1') {
            // Only send data for LED 1
            ledData = {
                led1: document.getElementById("led1").value
            };
        } else if (led === 'led2') {
            // Only send data for LED 2
            ledData = {
                led2: document.getElementById("led2").value
            };
        }

        fetch("/led", {
            method: "POST",
            headers: {
                "Content-Type": "application/json"
            },
            body: JSON.stringify(ledData)
        })
        .catch(error => console.error("Error sending LED data:", error));
    }

    setInterval(fetchSensorData, 1000);  // Update every 1 second

    document.getElementById("led1").addEventListener("input", sendLedData);
    document.getElementById("led2").addEventListener("input", sendLedData);
});
