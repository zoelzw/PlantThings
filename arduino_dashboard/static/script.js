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

    function sendLedData() {
        // Get the values of both sliders
        const led1Value = document.getElementById("led1").value;
        const led2Value = document.getElementById("led2").value;

        // Construct the message in the format "L, 1, value" and "L, 2, value"
        //const ledData = `L,1, ${led1Value}`;//`L,1,${led1Value}`;
        const ledData = { command: "L", led: 1, value: led1Value };

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
    //document.getElementById("led2").addEventListener("input", sendLedData);
});
