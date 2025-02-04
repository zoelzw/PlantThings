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

    function fetchSensorHistory() {
        fetch("/history")
            .then(response => response.json())
            .then(updateChart)
            .catch(error => console.error("Error fetching history:", error));
    }

    function sendLedData() {
        const ledData = {
            led1: document.getElementById("led1").value,
            led2: document.getElementById("led2").value,
            led3: document.getElementById("led3").value
        };

        fetch("/led", {
            method: "POST",
            headers: {
                "Content-Type": "application/json"
            },
            body: JSON.stringify(ledData)
        })
        .catch(error => console.error("Error sending LED data:", error));
    }

    // Set up the Chart.js chart
    const ctx = document.getElementById("sensorChart").getContext("2d");
    const sensorChart = new Chart(ctx, {
        type: "line",
        data: {
            labels: [],
            datasets: [
                { label: "Temperature (°C)", data: [], borderColor: "red", fill: false },
                { label: "Humidity (%)", data: [], borderColor: "blue", fill: false },
                { label: "CO₂ (ppm)", data: [], borderColor: "green", fill: false }
            ]
        },
        options: {
            responsive: true,
            scales: {
                x: { title: { display: true, text: "Time" } },
                y: { title: { display: true, text: "Values" } }
            }
        }
    });

    function updateChart(history) {
        sensorChart.data.labels = history.timestamps;
        sensorChart.data.datasets[0].data = history.temp;
        sensorChart.data.datasets[1].data = history.humidity;
        sensorChart.data.datasets[2].data = history.co2;
        sensorChart.update();
    }

    setInterval(fetchSensorData, 1000);
    setInterval(fetchSensorHistory, 1000);

    document.getElementById("led1").addEventListener("input", sendLedData);
    document.getElementById("led2").addEventListener("input", sendLedData);
    document.getElementById("led3").addEventListener("input", sendLedData);
});
