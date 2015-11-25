
/*check if it can be replaced by a % sign */
int overspill(int coordinate, int max);

int overspill(int coordinate, int max)
{
   int division;
   if (coordinate>(max-1)){
      division = coordinate/(max-1);
      coordinate -= (division*(max));
   }
   if (coordinate < 0){
     coordinate += (max);
   }
   return (coordinate);
}
