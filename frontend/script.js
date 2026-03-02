async function sendAccident() {
  const impactForce = document.getElementById("impact").value;
  const location = document.getElementById("location").value;

  const response = await fetch("http://localhost:5000/accident", {
    method: "POST",
    headers: {
      "Content-Type": "application/json"
    },
    body: JSON.stringify({ impactForce, location })
  });

  const data = await response.json();

  document.getElementById("result").innerHTML = `
    <div class="card">
      <h3>Result</h3>
      <p><strong>Severity:</strong> ${data.severity}</p>
      <p><strong>Assigned Hospital:</strong> ${data.hospital}</p>
      <p><strong>Status:</strong> ${data.message}</p>
    </div>
  `;
}
