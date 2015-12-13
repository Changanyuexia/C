void PrintTree(Root* root, Node* currentNode,Boolean isFirst)
{
  if (root==NULL)
    return;
  else if (root->right==NULL&&root->left==NULL)
    {
      root->PrintObject(root->value);
      return;
    }
  else if (currentNode!=NULL)
    {
      if(currentNode->left==NULL&&currentNode->right==NULL&&isFirst==FALSE)
        root->PrintObject(currentNode->value);
        return;
    }
  else
    {
      printf("(");
      if (isFirst==TRUE)
        {
          if (root->left!=NULL)
            {
              PrintTree(root,root->left,FALSE);
              printf("<");
            }
          root->PrintObject(root->value);

          if (root->right!=NULL)
            {
              printf(">");
              PrintTree(root,root->right, FALSE);
            }
        }
      else
        {

          if (currentNode->left!=NULL)
            {
              PrintTree(root,currentNode->left, FALSE);
              printf("<");
            }

          root->PrintObject(currentNode->value);

          if (currentNode->right!=NULL)
            {
              printf(">");
              PrintTree(root,currentNode->right, FALSE);
            }
        }
      printf(")");
    }
  return;
}
