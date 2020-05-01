module DecodeArticles = {
  let article: Js.Json.t => Types.article =
    json =>
      Json.Decode.{
        id: json |> field("id", string),
        author: json |> field("author", string),
        date_created: json |> field("date_created", string),
        title: json |> field("title", string),
      };

  let articles = Json.Decode.array(article);
};