/* lab11.cs
 * Nicholas Jordan
 * 11/24/2020
 * C# lab11 
 */

using System;

namespace Assignment {
  public class Application  {
    static void Main() {
      double rectWidth = 8.75f, rectHeight = 20.5f;
      IShape shape1 = new Rectangle(rectWidth, rectHeight);
      
      double triBase = 5.5f, triHeight = 12.25f;
      IShape shape2 = new Triangle(triBase, triHeight);

      double cirRadius = 5.5f;
      Circle shape3 = new Circle(cirRadius);
      //Test Radius property
      shape3.Radius = 3.5f;
      Console.WriteLine("Circle radius is {0}", shape3.Radius);

      Console.WriteLine("Area of type '{0}' = {1}", shape1, shape1.Area);
      Console.WriteLine("Area of type '{0}' = {1}", shape2, shape2.Area);  
      Console.WriteLine("Area of type '{0}' = {1}", shape3, shape3.Area);

      shape1.Display();
      shape2.Display();
      shape3.Display();
    }
  }

  public interface IShape {
     void Display ();
      
     double Area {
       get;    // concrete classes must implement IShape.Area.Get()
     }
  }

  ////////////////////////////////////////////////////////////////////////
  public class Rectangle: IShape {
     public Rectangle(double inWidth, double inHeight) {
        width = inWidth;
        height = inHeight;
     }
    
     public double Area {
        get { return width * height; }
     }

     public void Display() {
        Console.WriteLine("I'm a rectangle! I have width {0} and height {1}.", width, height);
     }

     private double width = 0;
     private double height = 0;
  }
  ////////////////////////////////////////////////////////////////////////
  public class Triangle: IShape {
    public Triangle(double inBase, double inHeight) {
        mybase = inBase;
        height = inHeight;
    }

    public double Area {
      get { return height * mybase / 2; }
    }

    public void Display() {
        Console.WriteLine("I'm a triangle! I have base {0} and height {1}.", mybase, height);
    }

    private double mybase = 0;
    private double height = 0;
  }

  ////////////////////////////////////////////////////////////////////////
  public class Circle: IShape {
    public Circle(double inRadius) {
        radius = inRadius;
    }

    public double Radius {
        get { return radius; }
        set { radius = value; }
    }

    public double Area {
        get { return radius * radius * PI; }
    }

    public void Display() {
        Console.WriteLine("I'm a circle! I have radius {0}.", radius);
    }

    private double radius = 0;
    private const double PI = 3.14;
  } 


} // end namespace 