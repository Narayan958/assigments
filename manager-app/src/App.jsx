import React, { useState } from "react";

function App() {
  const [students, setStudents] = useState([
    {
      id: 1,
      name: "Aditya",
      enrolledCourses: new Set(["Math", "Physics"]),
      gpa: 8.5,
    },
    {
      id: 2,
      name: "Hritik",
      enrolledCourses: new Set(["Math", "Chemistry"]),
      gpa: 9.1,
    },
    {
      id: 3,
      name: "Riya",
      enrolledCourses: new Set(["Physics", "Chemistry"]),
      gpa: 7.9,
    },
  ]);

  const [name, setName] = useState("");
  const [coursesInput, setCoursesInput] = useState("");
  const [gpa, setGpa] = useState("");
  const [filterCourse, setFilterCourse] = useState("");

  const addStudent = () => {
    if (!name.trim() || !gpa.trim()) return;

    // use Map internally (id -> student)
    const idToStudent = new Map(students.map((s) => [s.id, s]));
    const newId = students.length ? Math.max(...students.map((s) => s.id)) + 1 : 1;

    const coursesArray = coursesInput
      .split(",")
      .map((c) => c.trim())
      .filter((c) => c.length > 0);

    const newStudent = {
      id: newId,
      name,
      enrolledCourses: new Set(coursesArray),
      gpa: parseFloat(gpa),
    };

    idToStudent.set(newId, newStudent);

    // do not mutate state; use spread
    setStudents(Array.from(idToStudent.values()));

    setName("");
    setCoursesInput("");
    setGpa("");
  };

  const removeStudent = (id) => {
    // use filter (no direct mutation)
    setStudents(students.filter((s) => s.id !== id));
  };

  const sortedStudentsByGpa = [...students].reverse((a, b) => b.gpa - a.gpa);

  const allUniqueCourses = (() => {
    const courseSet = students.reduce((acc, s) => {
      s.enrolledCourses.forEach((c) => acc.add(c));
      return acc;
    }, new Set());
    // convert Set to array before rendering
    return Array.from(courseSet);
  })();

  const filteredStudents = filterCourse
    ? students.filter((s) => s.enrolledCourses.has(filterCourse))
    : students;

  return (
    <div style={{ padding: "20px" }}>
      <h2>Course Enrollment Dashboard</h2>

      <h3>Add New Student</h3>
      <div style={{ marginBottom: "10px" }}>
        <input
          type="text"
          placeholder="Name (e.g., Rohan)"
          value={name}
          onChange={(e) => setName(e.target.value)}
        />
        <input
          style={{ marginLeft: 8 }}
          type="text"
          placeholder="Courses (comma separated)"
          value={coursesInput}
          onChange={(e) => setCoursesInput(e.target.value)}
        />
        <input
          style={{ marginLeft: 8 }}
          type="number"
          step="0.1"
          placeholder="GPA"
          value={gpa}
          onChange={(e) => setGpa(e.target.value)}
        />
        <button style={{ marginLeft: 8 }} onClick={addStudent}>
          Add
        </button>
      </div>

      <h3>Filter by Course</h3>
      <select
        value={filterCourse}
        onChange={(e) => setFilterCourse(e.target.value)}
      >
        <option value="">All</option>
        {allUniqueCourses.map((course) => (
          <option key={course} value={course}>
            {course}
          </option>
        ))}
      </select>

      <h3 style={{ marginTop: "20px" }}>All Unique Courses</h3>
      <ul>
        {allUniqueCourses.map((course) => (
          <li key={course}>{course}</li>
        ))}
      </ul>

      <h3>Students (Sorted by GPA Descending)</h3>
      <ul>
        {sortedStudentsByGpa.map((s) => (
          <li key={s.id}>
            {s.name} (ID: {s.id}) - GPA: {s.gpa.toFixed(2)} - Courses:{" "}
            {Array.from(s.enrolledCourses).join(", ")}
            <button
              style={{ marginLeft: 8 }}
              onClick={() => removeStudent(s.id)}
            >
              Remove
            </button>
          </li>
        ))}
      </ul>

      <h3>Filtered Students by Course</h3>
      <ul>
        {filteredStudents.map((s) => (
          <li key={s.id}>
            {s.name} (ID: {s.id}) - GPA: {s.gpa.toFixed(2)}
          </li>
        ))}
      </ul>
    </div>
  );
}

export default App;
