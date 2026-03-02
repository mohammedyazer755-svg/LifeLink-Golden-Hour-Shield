const express = require("express");
const cors = require("cors");
const fs = require("fs");

const app = express();
app.use(cors());
app.use(express.json());
app.use(express.static("public"));

let db = JSON.parse(fs.readFileSync("database.json"));

// Severity classification logic
function classifySeverity(impactForce) {
  if (impactForce > 80) return "Major";
  if (impactForce > 40) return "Moderate";
  return "Minor";
}

// Smart hospital allocation
function allocateHospital(severity) {
  const eligible = db.hospitals
    .filter(h => h.level === severity && h.available)
    .sort((a, b) => a.distance - b.distance);

  return eligible.length > 0 ? eligible[0] : null;
}

// API to simulate accident
app.post("/accident", (req, res) => {
  const { impactForce, location } = req.body;

  const severity = classifySeverity(impactForce);
  const hospital = allocateHospital(severity);

  if (!hospital) {
    return res.json({
      message: "No hospital available",
      severity
    });
  }

  hospital.available = false;

  res.json({
    message: "Emergency Assigned",
    severity,
    hospital: hospital.name,
    location
  });
});

app.listen(5000, () => {
  console.log("LifeLink Server running on http://localhost:5000");
});
