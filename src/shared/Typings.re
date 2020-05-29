type dashboardArticle = {
  id: string,
  title: string,
  author: string,
  timing: int,
  date_created: string,
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