type dashboardArticle = {
  id: string,
  author: string,
  date_created: string,
  description: string,
  tags: array(string),
  timing: int,
  title: string,
};

type article = {
  id: string,
  title: string,
  author: string,
  timing: int,
  date_created: string,
  date_last_modified: string,
  is_modified: bool,
  data: string,
  tags: array(string),
};