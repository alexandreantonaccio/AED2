
   if (fin == NULL) {
      printf("Unable to open file.\n");
      return 2;
   }

   /* things seem to be ok, lets build the tree */
   char curline[MAXLEN];
   char command;
   int value;
   int count = 0;
   Node* r = newnode();
   Node** root = &r;

   while ( fgets(curline, MAXLEN, fin) ) {
      count++;
      if ( 2 != sscanf(curline, "%c %d", &command, &value)) {
         printf("Error parsing line %d\n",count);
         return 3;
      }
      //fprintf(stderr,"line: %d, %c, %d\n", count, command, value);
      if (command == 'I') {
         printNode(insert(root,value));
      } else if (command == 'S') {
         printNode(search(*root, value));
      } else {
         printf("Unrecognized command.\n");
      }
   }
   freetree(*root);