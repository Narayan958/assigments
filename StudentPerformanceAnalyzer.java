import java.util.*;
import java.util.stream.Collectors;

class Student {

    private int id;
    private String name;
    private List<String> courses;
    private Map<String, Integer> scores;

    public Student(int id, String name, List<String> courses, Map<String, Integer> scores) {
        this.id = id;
        this.name = name;
        this.courses = new ArrayList<>(courses);
        this.scores = new HashMap<>(scores);
    }

    public int getId(){ return id; }
    public String getName(){ return name; }
    public List<String> getCourses(){ return courses; }
    public Map<String,Integer> getScores(){ return scores; }

    public double getAverageScore(){
        return scores.values()
                .stream()
                .mapToInt(Integer::intValue)
                .average()
                .orElse(0.0);
    }
}

public class StudentPerformanceAnalyzer {

    public static List<Student> sortByAverageDescending(List<Student> students){
        return students.stream()
                .sorted(Comparator.comparingDouble(Student::getAverageScore).reversed())
                .collect(Collectors.toList());
    }

    public static List<Student> getTopNStudents(List<Student> students,int n){
        return sortByAverageDescending(students)
                .stream()
                .limit(n)
                .collect(Collectors.toList());
    }

    public static Map<String,Double> getAverageScorePerCourse(List<Student> students){

        Set<String> courses=getAllUniqueCourses(students);
        Map<String,Double> avgMap=new HashMap<>();

        for(String c:courses){
            double avg=students.stream()
                    .mapToInt(s->s.getScores().getOrDefault(c,0))
                    .average()
                    .orElse(0.0);
            avgMap.put(c,avg);
        }
        return avgMap;
    }

    public static Set<String> getAllUniqueCourses(List<Student> students){
        return students.stream()
                .flatMap(s->s.getCourses().stream())
                .collect(Collectors.toCollection(HashSet::new));
    }

    public static List<Student> getPassedStudents(List<Student> students){
        return students.stream()
                .filter(s->s.getScores().values().stream().allMatch(score->score>=40))
                .collect(Collectors.toList());
    }

    private static final String[] NAMES={
            "Aditya","Kaushal","Reddy","Rishab"
    };

    private static final String[] COURSE_POOL={
            "Math","Physics","Chemistry","English","Computer Science"
    };

    public static Student generateStudentWithName(int id,String name,Random rng){

        List<String> pool=new ArrayList<>(Arrays.asList(COURSE_POOL));
        Collections.shuffle(pool,rng);

        int numCourses=3+rng.nextInt(2);
        List<String> courses=new ArrayList<>(pool.subList(0,numCourses));

        Map<String,Integer> scores=new HashMap<>();

        for(String c:courses){
            scores.put(c,20+rng.nextInt(81));
        }

        return new Student(id,name,courses,scores);
    }

    public static List<Student> generateRandomStudents(int n,Random rng){

        List<Student> students=new ArrayList<>();

        List<String> names=new ArrayList<>(Arrays.asList(NAMES));
        Collections.shuffle(names,rng);

        for(int i=0;i<n;i++){
            String name=names.get(i%names.size());
            students.add(generateStudentWithName(i+1,name,rng));
        }

        return students;
    }

    public static void analyzeCourseAverageComplexity(){

        System.out.println("\n===== COMPLEXITY ANALYSIS: Course Averages =====");

        Random rng=new Random();
        int[] sizes={10,50,100,500,1000};
        int trials=1000;

        System.out.printf("%-10s %-20s\n","Students","Avg Time(ns)");

        for(int n:sizes){

            long total=0;

            for(int t=0;t<trials;t++){

                List<Student> students=generateRandomStudents(n,rng);

                long start=System.nanoTime();
                getAverageScorePerCourse(students);
                total+=System.nanoTime()-start;
            }

            System.out.printf("%-10d %-20d\n",n,total/trials);
        }

        System.out.println("\nTime Complexity : O(n * m)");
        System.out.println("Space Complexity: O(k)");
    }

    public static void analyzeSortingComplexity(){

        System.out.println("\n===== COMPLEXITY ANALYSIS: Sorting Students =====");

        Random rng=new Random();
        int[] sizes={10,50,100,500,1000};
        int trials=1000;

        System.out.printf("%-10s %-20s\n","Students","Avg Time(ns)");

        for(int n:sizes){

            long total=0;

            for(int t=0;t<trials;t++){

                List<Student> students=generateRandomStudents(n,rng);

                long start=System.nanoTime();
                getTopNStudents(students,2);
                total+=System.nanoTime()-start;
            }

            System.out.printf("%-10d %-20d\n",n,total/trials);
        }

        System.out.println("\nTime Complexity : O(n log n)");
        System.out.println("Space Complexity: O(n)");
    }

    public static void main(String[] args){

        Random rng=new Random();

        List<Student> students=generateRandomStudents(4,rng);

        System.out.println("===== RANDOM STUDENTS =====");

        for(Student s:students){

            System.out.println("\nID   : "+s.getId());
            System.out.println("Name : "+s.getName());
            System.out.println("Scores: "+s.getScores());
        }

        System.out.println("\n===== Sorted By Average =====");

        sortByAverageDescending(students)
                .forEach(s->System.out.printf("%-10s Avg=%.2f\n",s.getName(),s.getAverageScore()));

        System.out.println("\n===== Top 2 Students =====");

        getTopNStudents(students,2)
                .forEach(s->System.out.printf("%-10s Avg=%.2f\n",s.getName(),s.getAverageScore()));

        System.out.println("\n===== Average Per Course =====");

        getAverageScorePerCourse(students)
                .forEach((c,a)->System.out.printf("%-20s %.2f\n",c,a));

        System.out.println("\n===== Unique Courses =====");
        System.out.println(getAllUniqueCourses(students));

        System.out.println("\n===== Passed Students =====");

        getPassedStudents(students)
                .forEach(s->System.out.println(s.getName()));

        analyzeCourseAverageComplexity();
        analyzeSortingComplexity();
    }
}