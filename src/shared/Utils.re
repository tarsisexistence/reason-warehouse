module DecodeArticles = {
  let article: Js.Json.t => Types.dashboardArticle =
    json =>
      Json.Decode.{
        id: json |> field("id", string),
        author: json |> field("author", string),
        date_created: json |> field("date_created", string),
        title: json |> field("title", string),
        timing: json |> field("timing", int),
      };

  let articles = Json.Decode.array(article);
};

module DecodeArticle = {
  let article: Js.Json.t => Types.article =
    json =>
      Json.Decode.{
        id: json |> field("id", string),
        author: json |> field("author", string),
        date_created: json |> field("date_created", string),
        title: json |> field("title", string),
        timing: json |> field("timing", int),
        data: json |> field("data", string),
        date_last_modified: json |> field("date_last_modified", string),
        is_modified: json |> field("is_modified", bool),
        tags: json |> field("tags", array(string)),
      };
};

module Common = {
  let getMonthName = monthOrder =>
    switch (monthOrder) {
    | 0 => "January"
    | 1 => "February"
    | 2 => "March"
    | 3 => "April"
    | 4 => "May"
    | 5 => "June"
    | 6 => "July"
    | 7 => "August"
    | 8 => "September"
    | 9 => "October"
    | 10 => "November"
    | 11 => "December"
    | _ => "Never"
    };

  let getTimeDescription = (article: Types.article) => {
    let date = Js.Date.fromString(article.date_created);
    let month = date |> Js.Date.getMonth |> int_of_float |> getMonthName;
    let day = date |> Js.Date.getDate;
    let year = date |> Js.Date.getFullYear;
    let readingTime =
      (article.timing |> Js.Int.toFloat) /. 60.0 |> Js.Math.ceil;
    {j|$month $day, $year • $readingTime min read|j};
  };
};