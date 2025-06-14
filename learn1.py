if __name__ == "__main__":
   x = (int (input("Enter the number of numbers: ")))
   odd = 0
   even = 0
   for i in range (x):
      print("No.{0}:".format(i+1), end= " ")
      a = (int(input()))
      if a%2 == 0:
        even += a
      else :
        odd += a
   print("The sum of odd numbers is:", odd)
   print("The sum of even numbers is:", even)
       
         



