class Course:
    def __init__(self, course_id, name, credits, grading_type="Standard"):
        self.course_id = course_id
        self.name = name
        self.credits = credits
        self.grading_type = grading_type
        self.grades = {}

class Student:
    def __init__(self, student_id):
        self.student_id = student_id
        self.courses = []

class CourseRegistrationSystem:
    def __init__(self):
        self.courses = {}
        self.students = {}

    def create_course(self, course_id, name, credits, grading_type="Standard"):
        if course_id in self.courses or any(course.name == name for course in self.courses.values()):
            return "false"
        self.courses[course_id] = Course(course_id, name, credits, grading_type)
        return "true"

    def register_for_course(self, student_id, course_id):
        if course_id not in self.courses:
            return "false"
        
        if student_id not in self.students:
            self.students[student_id] = Student(student_id)
        
        student = self.students[student_id]
        course = self.courses[course_id]
        
        if course in student.courses:
            return "false"
        
        total_credits = sum(c.credits for c in student.courses) + course.credits
        if total_credits > 24:
            return "false"
        
        student.courses.append(course)
        return "true"

    def set_component_grade(self, student_id, course_id, component, grade):
        if course_id not in self.courses or student_id not in self.students:
            return "invalid"
        
        student = self.students[student_id]
        course = self.courses[course_id]
        
        if course not in student.courses:
            return "invalid"
        
        if student_id not in course.grades:
            course.grades[student_id] = {"midterm": None, "final": None, "homeworks": None}
        
        if course.grades[student_id][component] is None:
            course.grades[student_id][component] = grade
            return "set"
        else:
            course.grades[student_id][component] = grade
            return "updated"

    def get_gpa(self, student_id, department=None):
        if student_id not in self.students:
            return ""
        
        student = self.students[student_id]
        total_credits = 0
        total_grade_points = 0
        pass_count = 0
        fail_count = 0
        
        for course in student.courses:
            if department and not course.course_id.startswith(department):
                continue
            
            if course.grading_type == "Standard":
                grades = course.grades.get(student_id, {})
                if None in grades.values():
                    return ""
                total = sum(grades.values())
                total_credits += course.credits
                total_grade_points += total * course.credits
            elif course.grading_type == "Pass/Fail":
                grades = course.grades.get(student_id, {})
                if None in grades.values():
                    return ""
                total = sum(grades.values())
                if total >= 66:
                    pass_count += 1
                else:
                    fail_count += 1
        
        if total_credits == 0:
            return ""
        
        gpa = total_grade_points // total_credits
        return f"{gpa},{pass_count},{fail_count}"

    def get_best_student_nominees(self):
        department_gpas = {}
        for student_id, student in self.students.items():
            dept_courses = {}
            for course in student.courses:
                if course.grading_type == "Standard":
                    dept = course.course_id[:3]
                    if dept not in dept_courses:
                        dept_courses[dept] = 0
                    dept_courses[dept] += 1
            
            for dept, count in dept_courses.items():
                if count >= 2:
                    gpa_result = self.get_gpa(student_id, dept)
                    if gpa_result:
                        gpa, _, _ = map(int, gpa_result.split(","))
                        if dept not in department_gpas:
                            department_gpas[dept] = []
                        department_gpas[dept].append((student_id, gpa))
        
        best_students = {}
        for dept, students in department_gpas.items():
            best_students[dept] = max(students, key=lambda x: x[1])
        
        sorted_departments = sorted(best_students.items())
        result = ', '.join(f'{dept} - ({student_id}, {gpa})' for dept, (student_id, gpa) in sorted_departments)
        return result if sorted_departments else ""

# Example usage
system = CourseRegistrationSystem()
print(system.create_course("CSE220", "Data Structures", 3, "Standard"))  # "true"
print(system.create_course("CSE300", "Introduction to Algorithms", 3, "Standard"))  # "true"
print(system.create_course("CSE330", "Operating Systems", 4, "Pass/Fail"))  # "true"
print(system.register_for_course("st002", "CSE220"))  # "true"
print(system.register_for_course("st002", "CSE300"))  # "true"
print(system.set_component_grade("st002", "CSE220", "midterm", 80))  # "set"
print(system.set_component_grade("st002", "CSE220", "final", 90))  # "set"
print(system.set_component_grade("st002", "CSE220", "homeworks", 85))  # "set"
print(system.set_component_grade("st002", "CSE300", "midterm", 85))  # "set"
print(system.set_component_grade("st002", "CSE300", "final", 88))  # "set"
print(system.set_component_grade("st002", "CSE300", "homeworks", 87))  # "set"
print(system.get_gpa("st002"))  # Example of computing GPA
print(system.get_best_student_nominees())  # Example of getting best student nominees
